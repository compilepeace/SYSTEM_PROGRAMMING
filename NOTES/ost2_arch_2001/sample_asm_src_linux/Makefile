
CC 	= gcc 
CXX = g++
AS  = yasm 
ASFLAGS	= -f elf64 -g dwarf2
CFLAGS	= -g -Werror


TARGETS = cpuid
all: $(TARGETS)


cpuid: cpuid.asm
	$(AS) $(ASFLAGS) $<
	$(CC) $(CFLAGS) $@.o $@.c -o $@

clean: 
	rm *.o $(TARGETS)
	
	

