/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#include<stdio.h>
#include<stdint.h>

/* This function executes in THREAD MODE of the processor */
void generate_interrupt()
{
	uint32_t *pSTIR  = (uint32_t*)0xE000EF00;
	uint32_t *pISER0 = (uint32_t*)0xE000E100;

	//enable IRQ3 interrupt
	*pISER0 |= ( 1 << 3);

	//generate an interrupt from software for IRQ3
	*pSTIR = (3 & 0x1FF);

}

/* This function executes in THREAD MODE of the processor */
int main(void)
{
	int control_reg = 0x2;
	uint32_t psp_value = 0x20008000;

   /* this code modifies the CONTROL register for SP selection (to PSP instead of default MSP) */
	// when ISR (RTC_WKUP_IRQhandler()) returns, PC will retrieve EXC_RETURN of 0xfffffffd from SP
	// 0xd = 1101 => indicating the processor to return to thread mode with PSP as SP
	__asm volatile ("msr PSP,%0"::"r"(psp_value));
	__asm volatile ("msr CONTROL,%0"::"r"(control_reg));
	// without the above inline assembly, PC will retrieve a value of  0xfffffff9 (EXC_RETURN) from SP
	// 0x9 = 1001 => indicating the processor to return to thread mode with MSP as SP

	printf("In thread mode : before interrupt\n");

	generate_interrupt();

	printf("In thread mode : after interrupt\n");

	for(;;);
}

/* This function(ISR) executes in HANDLER MODE of the processor */
void RTC_WKUP_IRQHandler(void)
{
	printf("In handler mode : ISR\n");
}
