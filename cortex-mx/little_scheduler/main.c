/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "led.h"

/*
 * SCHEDULER DESIGN
 * This bare-metal application has 2 parts of CODE - Scheduler and user-mode Tasks.
 * 1. create 4 user-mode tasks in application program
 * 2. stack management for application - stack pointer selection.
 * 		> using PSP to trace stack utilization of user-mode tasks
 * 		> using MSP for scheduler stack.
 *  	> reserving stack areas for all the created tasks and scheduler (macros)
 * 4. scheduling policy selection, this could be based on below factors
 * 		> process’s priority
 * 		> process’s privilege level
 *    	> how long has the process already been consuming the CPU.
 * 5. configure the systick TIMER to produce exception for every 1ms.
 * 		> what will be the count value of timer (check systick timer count clock in MCU HSR clock)
 * 		>
 *
 * DESIGN LIMITATIONS -
 * Currently, each component of application (scheduler and every task) is only differentiated based
 * on their respective stack regions.
 *
 * 1. PROCESSOR resource
 * 	  As a system/kernel designer - to decide whether to allow access to system resources or not -
 *    code should be categorised as kernel-mode and user-mode task where both scheduler and tasks
 *    should be differentiated based on operational mode (thread/handler) and privilege level (rings)
 *    of processor.
 * 2. MEMORY resource
 *    Both tasks and scheduler current have access to entire SRAM memory, including their stack
 *    segment. If task1 has a bug which allows for arbitrary read/write (let's say buffer overflow
 *    in stack segment), it can access/corrupt control point of another task's stack memory region -
 *    stack frame (which it shouldn't have access to). This might result into arbitrary code execution
 *    when the corrupted task is allocated CPU by scheduler (update_next_task()). There should be
 *    separation of SRAM memory regions as kernel-space and user-space where only privileged-code
 *    should have access to kernel-space and unprivileged-code should have access to user-space
 *    memory region of SRAM memory.
 * 3. To prevent race condition between user-mode & handler-mode code, we've serialized access to
 * 	  shared data using INTERRUPT_DISABLE & INTERRUPT_ENABLE macro, this should be avoided in
 * 	  RTOS or embedded kernel scheduler implementations as disabling the interrupt (even for a
 * 	  short duration) can be fatal.
 */


void enable_processor_faults(void);
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_stack_start);
void init_tasks_stack(void);
void init_systick_timer (uint32_t tick_hz);
uint32_t get_psp_of_current_task(void);
__attribute__((naked)) void switch_sp_to_psp(void);
void task1_handler(void);	// user-mode Task 1 of bare-metal software application
void task2_handler(void);	// user-mode Task 2 of bare-metal software application
void task3_handler(void);	// user-mode Task 3 of bare-metal software application
void task4_handler(void);	// user-mode Task 4 of bare-metal software application
void save_psp_value(uint32_t current_psp);
void update_next_task(void);
void schedule ();
void task_delay (uint32_t tick_count);		// should block the task for tick_count systick exceptions
void idle_task (void);
void unblock_tasks(void);

// semi-hosting init function (librdimon_nano.a by specs=rdimon.specs)
extern void initialise_monitor_handles(void);

// TASK CONTROL BLOCK - stores info. required by the scheduler about a task
typedef struct {
	uint32_t psp_value;
	uint32_t block_count;		// block duration : count=1000 ticks means 1000 systick exceptions.
	uint8_t current_state;		// running state
	void (*task_handler)(void);
}TCB_t;
TCB_t user_tasks[MAX_TASKS];	// shared between handler-mode & thread-mode code
uint8_t current_task = 1;		// as 0 is IDLE task which should only run when all other task are in blocked state
uint32_t g_tick_count = 0;		// initialize global systick exception counts.

/*
 * SysTick count value calculation
 * - Processor clock = 16 MHz
 * - SysTick timer count clock = 16 MHz (frequency = 16*10^6 counts per second)
 * 	> 1ms is 1KHz in frequency domain
 * 	> we want 1000 sys tick exceptions in 1 second
 * - So, to bring down SysTick timer count clock from 16 MHz to 1 KHz use a divisor (count/reload value)
 * - Therefore, reload value should be = 16000
 *
 * 	16000000 Hz (clock freq) / 16000 (count value) = 1000 Hz (1000 exceptions per second) (TICK_HZ - desired exception frequency)
 */
int main(void)
{
	printf ("little scheduler x_x\n");

	// we might do some illegal activities (with stack) which need to pop up before us in order to be diagnosed.
	enable_processor_faults();

	// change current SP (MSP) to scheduler stack region
	// so that scheduler runs withing its own stack boundaries.
	init_scheduler_stack (SCHED_STACK_START);

	// initializing user-mode task control blocks/structures and their stack with dummy frames or dummy context
	init_tasks_stack();

	led_init_all();				// initialize LEDs of discovery board.

	// initialize scheduler frequency
	init_systick_timer (TICK_HZ);		// start the systick counter to allow scheduler to come into action (systick exception)

	/* Launch tasks - before calling a task their stack pointer must be changed to use PSP instead of MSP being current SP*/
	switch_sp_to_psp();
	task1_handler();			// alternatively you can use svc #N interrupt to do that (like syscalls)

    /* Loop forever */
	for(;;);
}

// change stack pointer (SP or MSP) to use scheduler's stack region.
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_stack_start)
{
	__asm volatile ("MSR msp, %0": :"r"(sched_stack_start):);
	__asm volatile ("bx lr");
}

// initialize stack for every Task to store a dummy context before they're created.
// when scheduler wants to switch context to INITIALLY start a task, it retrieves
// this dummy context by poping context off from new task's stack region (pointed to by PSP).
void init_tasks_stack(void)
{
	// initialize current state for user tasks
	user_tasks[0].current_state = TASK_READY_STATE;		// idle task- always in ready state
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;
	user_tasks[4].current_state = TASK_READY_STATE;

	// initialize PSP values for user tasks
	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[1].psp_value = T1_STACK_START;
	user_tasks[2].psp_value = T2_STACK_START;
	user_tasks[3].psp_value = T3_STACK_START;
	user_tasks[4].psp_value = T4_STACK_START;

	// initialize task handler for user tasks
	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = task1_handler;
	user_tasks[2].task_handler = task2_handler;
	user_tasks[3].task_handler = task3_handler;
	user_tasks[4].task_handler = task4_handler;


	uint32_t *pPSP;
	for (int i = 0 ; i < MAX_TASKS; ++i)
	{
		pPSP = (uint32_t *)user_tasks[i].psp_value;		// get stack start of task i (0,1,2,3)

		// store status register (following strdb - store decrement before)
		--pPSP;
		*pPSP = DUMMY_XPSR;		// 0x01000000 - set 24th bit, i.e. T-bit (Thumb mode)

		// PC
		--pPSP;
		*pPSP = (uint32_t )user_tasks[i].task_handler;	// tells from what memory location to start executing the task.

		// LR - EXEC_RETURN value for exception handler
		--pPSP;
		*pPSP = 0xfffffffd;		// specifies the NEW- SP (MSP/PSP) and execution mode (handler/thread)

		// store default values of registers r0-r12
		for (int gpr = 0; gpr < 13; ++gpr){
			--pPSP;
			*pPSP = 0;
		}

		user_tasks[i].psp_value = (uint32_t )pPSP;		// save new PSP for current task
	}
}

// Initialize scheduler frequency - tick_hz is input clock to the systick timer.
void init_systick_timer (uint32_t tick_hz)
{
	// count is the number of times systick interrupt will get triggered in 1 second.
	// check cortex-m4 to find out where we have to configure the reload/count value (section 4.4.2)
	uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz) - 1;

	// configure SVR only
	// Do NOT configure CVR (current value register), as it is implicitly decremented at each clock cycle
	// and will copy a fresh value from SVR when its value reaches (which takes 1 clock cycle) AND
	// at this moment (getting value from SVR) sysTick exception will get triggered.
	// Therefore, if sysTick is required every 100 clock pulses, set RELOAD/count-value to 99.
	uint32_t *pSRVR = (uint32_t *)0xE000E014;
	uint32_t *pSCSR = (uint32_t *)0xE000e010;

	// clean Reload Value Register
	*pSRVR &= ~(0x00ffffffff);

	// load count value in SRVR
	*pSRVR |= count_value;

	// tweak some settings here via - SCSR (systick control and status register)
	*pSCSR |= (1 << 1);		// Enables sysTick exception request
	*pSCSR |= (1 << 2);		// Indicates clock source - processor's clock

	// enable the systick counter (exception)
	*pSCSR |= (1 << 0);		// enables/starts the counter

}

void save_psp_value(uint32_t current_psp)
{
	user_tasks[current_task].psp_value = current_psp;
}

// choose a task from user_task to update current_task using round-robin algorithm.
void update_next_task(void)
{
	int state = TASK_BLOCKED_STATE;

	// iterate over user_task list
	for (int i = 0 ; i < MAX_TASKS; ++i)
	{
		++current_task;
		current_task %= MAX_TASKS;
		state = user_tasks[current_task].current_state;
		if ( (state == TASK_READY_STATE) && (current_task != 0) )	// ignore idle task
			break;
	}

	// run IDLE_TASK if all other tasks are currently blocked.
	if (state != TASK_READY_STATE)
		current_task = 0;
}

uint32_t get_psp_of_current_task(void)
{
	return user_tasks[current_task].psp_value;
}

// At the time of call to this function, LR automatically gets populated with a return-address in caller (i.e. main())
__attribute__((naked)) void switch_sp_to_psp(void)
{
	// 1. initialize PSP with task1's stack start address location.
	// get the value of PSP of current task with constraints -
	// - preserve LR which connects back to main()
	// - initialize PSP with current tasks stack region.
	// - pop back LR
	//get_psp_of_current_task();
	__asm volatile ("push {lr}");
	__asm volatile ("bl get_psp_of_current_task");		// this overwrites value inside LR which we'll need later to reach back to main()
	__asm volatile ("msr psp, r0");
	__asm volatile ("pop {lr}");

	// 2. from now on, use PSP as stack pointer
	// this can be done by changing SP to PSP using CONTROL register
	// till this point, we've been using MSP as SP.
	__asm volatile ("mov r0, #0x02");		// set the 2nd bit on CONTROL register specifying PSP is SP
	__asm volatile ("msr CONTROL, r0");
	__asm volatile ("bx lr");			// indirect branch - use LR to go back to main
}

//---------------------------------------------------------------------------------------
// TASKS implementation

void task1_handler(void)
{
	printf ("task1 started...\n");
	while (1){
		led_on(LED_GREEN);
		printf ("[+] task1: turned LED = ON\n");
		task_delay(TICK_HZ);		// every second
		led_off(LED_GREEN);
		printf ("[-] task1: turned LED = OFF\n");
		task_delay(TICK_HZ);
	};
}

void task2_handler(void)
{
	printf ("task2 started...\n");
	while (1){
		led_on(LED_ORANGE);
		printf ("[+] task2: turned LED = ON\n");
		task_delay(TICK_HZ/2);		// every 0.5 seconds
		led_off(LED_ORANGE);
		printf ("[-] task2: turned LED = OFF\n");
		task_delay(TICK_HZ/2);
	};
}

void task3_handler(void)
{
	printf ("task3 started...\n");
	while (1){
		led_on(LED_BLUE);
		printf ("[+] task3: turned LED = ON\n");
		task_delay(TICK_HZ/4);		// every 0.25 seconds
		led_off(LED_BLUE);
		printf ("[-] task3: turned LED = OFF\n");
		task_delay(TICK_HZ/4);
	};
}

void task4_handler(void)
{
	printf ("task4 started...\n");
	while (1){
		led_on(LED_RED);
		printf ("[+] task4: turned LED = ON\n");
		task_delay(TICK_HZ/8);		// every 0.125 seconds
		led_off(LED_RED);
		printf ("[-] task4: turned LED = OFF\n");
		task_delay(TICK_HZ/8);
	};
}
//---------------------------------------------------------------------------------------


void enable_processor_faults(void)
{
	// 1. enable fault handlers via registers (check registers in SCB)
	// SHCSR - system handler control and status register
	uint32_t  *pSHCSR = (uint32_t *) 0xE000ED24;
	*pSHCSR |= (1 << 16);		// enable mem-manage fault
	*pSHCSR |= (1 << 17);		// enable bus fault
	*pSHCSR |= (1 << 18);		// enable usage fault
}

// simply pends the pendSV bit - which causes the pendSV exception to perform context switch
void schedule ()
{
	// postpone the context switch (complex task) after all current ISRs (if any) are processed.
	// this can be done by pending the pendSV bit in ICSR (NVIC register)
	// set 28th bit to 1 (PEND state) for PENDSVSET (check cortex-m4 generic user guide)
	uint32_t *pICSR = (uint32_t*)0xE000ED04;
	*pICSR |= ( 1 << 28);
}

// why ? current task calls it to get into a blocked state (delay period specified by tick_count)
void task_delay (uint32_t tick_count)
{
	// To serialize access to shared resource (user_tasks), we disable interrupts i.e. no
	// interrupts or exceptions (handler mode code) should run.
	INTERRUPT_DISABLE();

	// scheduler should unblock the task when its global tick count (g_tick_count -
	// maintained by sysTick/scheduler)reaches this task's block_count.
	// For this reason, we decided block duration to be with reference to global
	// tick count.
	if (current_task != 0)		// current task should not be IDLE task
	{
		user_tasks[current_task].block_count = g_tick_count + tick_count;
		user_tasks[current_task].current_state = TASK_BLOCKED_STATE;

		// now that current task went into block state, allocate CPU to some other
		// READY task.
		schedule();
	}

	INTERRUPT_ENABLE();
}

// to allow CPU to execute something when all tasks are in blocked state
void idle_task (void)
{
	while (1){};
}

// update ready state for all tasks whose block_count is equal to global systick count
void unblock_tasks(void)
{
	for (int i = 1; i < MAX_TASKS; ++i)
	{
		if (user_tasks[i].current_state != TASK_READY_STATE &&
				user_tasks[i].block_count == g_tick_count)
		{
			user_tasks[i].current_state = TASK_READY_STATE;
		}
	}
}

/*
 * Scheduling is an algorithm which decides what running task to pre-empt and which task
 * should run next on the CPU.
 * This decision could be based on many factors -
 * 	> system load
 * 	> shared resource access
 * 	> simple round-robin method
 */
void SysTick_Handler()
{
	g_tick_count++;		// update global tick count
	unblock_tasks();

	// postpone the context switch (complex task) after all current ISRs (if any) are processed.
	// this can be done by pending the pendSV bit in ICSR (NVIC register)
	// set 28th bit to 1 (PEND state) for PENDSVSET (check cortex-m4 generic user guide)
	uint32_t *icsr = (uint32_t *)0xE000ED04;
	*icsr |= (0x1 << 28);
}

// responsible for performing context switch (i.e. saving current & retrieving next task's state)
__attribute__((naked)) void PendSV_Handler(void)
{
	// save the context of current task
	// 1. get current running task's stack location (PSP value)
	// 2. save context (SF2 = R4-R11) on task stack (because SF1 is already stored by stacking at exception trigger)
	// 3. save the current task's stack location (current PSP)
	__asm volatile ("mrs r0, psp");
	__asm volatile ("stmdb r0!, {r4-r11}");
	// since we're using bl instruction within this body, we don't want
	// EXEC_RETURN value (stored during exception stacking) to get corrupted
	__asm volatile ("push {lr}");
	__asm volatile ("bl save_psp_value");

	// retrieve the context of next task
	// 1. decide next task to run
	__asm volatile ("bl update_next_task");
	// 2. get its past stack location (PSP value)
	__asm volatile ("bl get_psp_of_current_task");
	// 3. retrieve context (SF2 = R4-R11) from PSP retrieved. (because SF1 is already retrieved by unstacking process after exception handler returns)
	__asm volatile ("ldmia r0!, {r4-r11}");
	// 4. update PSP and exit.
	__asm volatile ("msr psp, r0");

	// the exit will happen when the value of EXEC_RETURN is copied into PC.
	// at exit, processor will try to fetch SF1 (stack frame 1) from PSP
	__asm volatile ("pop {lr}");
	__asm volatile ("bx lr"); 		// EXEC_RETURN is copied into PC & exit-sequences (unstacking) triggers
}

void HardFault_Handler(void)
{
	printf ("Inside ISR: system exception generated - Hardfault\n");
}

void MemManage_Handler(void)
{
	printf ("Inside ISR: system exception generated - MemManage\n");
}

void BusFault_Handler(void)
{
	printf ("Inside ISR: system exception generated - BusFault\n");
}


__attribute__((naked)) void UsageFault_Handler(void)
{
	__asm volatile ("mrs r0, msp");
	__asm volatile ("b UsageFault_Handler_c");
}

void UsageFault_Handler_c(uint32_t *sp)
{
	//__asm volatile ("mrs r5,msp");
	// register attribute means "do not create this variable on stack", rather
	// use register r0 to hold the value of this variable (msp_value).
	//register uint32_t msp_value __asm("r5");

	// PRINT the CONTEXT saved by processor on stack (when exception is triggered)
	printf ("Inside ISR: system exception generated - UsageFault\n");
	printf ("pBaseStackPointer	: 0x%lx\n", (uint32_t )sp);
	printf ("r0					: 0x%lx\n", sp[0]);
	printf ("r1					: 0x%lx\n", sp[1]);
	printf ("r2					: 0x%lx\n", sp[2]);
	printf ("r3					: 0x%lx\n", sp[3]);
	printf ("r12				: 0x%lx\n", sp[4]);
	printf ("LR					: 0x%lx\n", sp[5]);
	printf ("PC					: 0x%lx\n", sp[6]);
	printf ("xpsr				: 0x%lx\n", sp[7]);
}
