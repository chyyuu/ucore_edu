make test 
	this sample is to demo ucore elf run itself

make test2
	this sample is to demo how boot code load the ucore elf to its execute addr and run by jmp instruction (using function pointer)


these files should be read for understand the internals 

boot.lds
==========

	ENTRY(_start)

	SECTIONS
	{
		. = 0x0;
		.text : { *(.text) }
		.bss : { *(.bss) }

		. = 0x1000;
		kernel_start = .;
		.data : { ucore.o }
		kernel_start_end = .;
	}


ucore.lds
===========

ENTRY(_start)

SECTIONS
{
	. = 0x108000;	/* 1M + 32k */
	.text : { *(.text) }
	.data : { *(.data) }
	.bss : { *(.bss) }
}


Makefile 
===========

all:
	make ucore
	make bootloader

ucore:
	arm-linux-as entry.S -o entry.o
	arm-linux-gcc -c init.c stdio.c uart.c
	arm-linux-ld -Tucore.lds entry.o init.o stdio.o uart.o -o ucore.elf
	arm-linux-objdump -D ucore.elf > ucore.lst

bootloader:
	arm-linux-as boot.S -o boot.o
	arm-linux-gcc -c main.c 
	arm-linux-ld -r -o ucore.o -b binary ucore.elf
	arm-linux-ld -Tboot.lds boot.o main.o ucore.o -o boot_ucore.elf
	arm-linux-objdump -D boot_ucore.elf > boot_ucore.lst

test:
	emulator-arm -avd tester -kernel ucore.elf -no-window -qemu -serial stdio

test2:
	emulator-arm -avd tester -kernel boot_ucore.elf -no-window -qemu -serial stdio

clean:
	-rm *.o
	-rm *.elf
