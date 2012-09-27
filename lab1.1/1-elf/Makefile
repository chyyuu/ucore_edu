all:
	make ucore
	make bootloader
	@echo "\nyou can 'make test' or 'make test2' to run demo, see README.md for details"

ucore:
	arm-eabi-as entry.S -o entry.o
	arm-eabi-gcc -c init.c stdio.c uart.c
	arm-eabi-ld -Tucore.lds entry.o init.o stdio.o uart.o -o ucore.elf
	arm-eabi-objdump -D ucore.elf > ucore.lst

bootloader:
	arm-eabi-as boot.S -o boot.o
	arm-eabi-gcc -c main.c 
	arm-eabi-ld -r -o ucore.o -b binary ucore.elf
	arm-eabi-ld -Tboot.lds boot.o main.o ucore.o -o boot_ucore.elf
	arm-eabi-objdump -D boot_ucore.elf > boot_ucore.lst

test:
	emulator-arm -avd tester -kernel ucore.elf -no-window -qemu -serial stdio

test2:
	emulator-arm -avd tester -kernel boot_ucore.elf -no-window -qemu -serial stdio

clean:
	-rm -f *.o *.elf *.lst
