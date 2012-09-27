all:
	make ucore
	make bootloader
	@echo "\nyou can 'make test' or 'make test2' to run demo, see README.md for details"

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
	-rm *.lst
