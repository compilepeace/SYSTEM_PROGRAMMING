
CC 	= gcc 
CXX = g++
AS  = yasm 
ASFLAGS	= -f elf64 -g dwarf2
CFLAGS	= -g -Werror
#LDFLAGS = 
# a program when linked with 'ld' has its interpreter specified
# as /lib/ld64.so.1 (inside PT_INTERP segment) which is sometimes
# not present on the system. In this case, the binary cannot be executed 

TARGETS = calling_asm_from_c calling_libc_from_asm
all: $(TARGETS)


calling_asm_from_c: calling_asm_from_c.asm
	$(AS) $(ASFLAGS) $<
	$(CC) $@.o main.c -o $@

calling_libc_from_asm: calling_libc_from_asm.asm
	$(AS) $(ASFLAGS) $<
	$(CC) -no-pie $@.o -o $@

clean: 
	rm *.o $(TARGETS)
	
	

