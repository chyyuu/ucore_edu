all:
	arm-eabi-as entry.S -o entry.o
	arm-eabi-gcc -c init.c stdio.c uart.c
	arm-eabi-ld -Tucore.lds *.o -o ucore.elf
	arm-eabi-objdump -D ucore.elf > ucore.lst
	@echo "\nyou can 'make test' to run demo"

test:
	emulator-arm -avd tester -kernel ucore.elf -no-window -qemu -serial stdio

clean:
	-rm -f *.o *.elf
