# Custom Scheduler
This is a scheduler code written as a part of my journey in learning bare-metal programming for ARM based processors. Target board specifications -

- board = STM32F407G-DISC1
- MCU   = Stm32f407 VGT6U
- CPU   = ARM Cortex-m4

**NOTE** - checkout the MCU reference manual for details about peripheral specs (like FLASH, SRAM size etc.)

## BUILD
To see printf(3) style messages while debugging, build semihosting compatible binary.

```
$ make			# build final.elf - production style binary
$ make semi		# build final_sh.elf with semihosting support
```
The difference is mainly in library linked (statically) to the binary. For semi-hosting feature, `librdimon_nano.a` is used (via spec file rdimon.specs), otherwise `libc_nano.a` is used (via spec file nano.specs).

## RUN or DEBUG
To execute *final.elf* or *final_sh.elf* on target board.

On terminal session 1
```
$ make load
OR
$ openocd -f board/stm32f4discovery.cfg
OR
$ openocd -f ls /usr/share/openocd/scripts/board/stm32f4discovery.cfg 
```

On terminal session 2
```
$ gdb-multiarch ./final_sh.elf 
(gdb) target extended-remote:3333
OR
(gdb) target remote:3333
(gdb) monitor arm semihosting enable
(gdb) monitor flash write_image erase final_sh.elf
(gdb) monitor reset

target should be running now... 
check LEDs should blink in a pattern...

# to stop target at RESET handler (1st instruction executed by CPU)
(gdb) monitor reset halt
```

## CODE Organization

- **final.map** - linker generated file describing memory-map of application, i.e. allows to check sections-to-segment mappping of final.elf
- **led.c** - defines LED on and off functions
- **main.c** - defines main scheduler component and thread-mode task.
- **stm32_ls.ld** - linker script to organise (merge + locate) code & data sections in segments. 
- **stm32_startup.c** - startup code defining vector table, Reset_Handler() and default exception handler (ISR for all undefined interrupts)
- **syscall.c** - defines syscall wrappers.