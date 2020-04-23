obj-m += 00_hello_kernel_lkm.o 01_golden_ratio_prime_lkm.o 02_gcd_lkm.o 03_system_uptime_lkm.o 04_lifetime_in_kernel_space_lkm.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
