all:
	arm-linux-as entry.S -o entry.o
	arm-linux-gcc -c init.c stdio.c uart.c
	arm-linux-ld -Tucore.lds *.o -o ucore.elf
	arm-linux-objdump -D ucore.elf > ucore.lst
	@echo "\nyou can 'make test' to run demo"

test:
	emulator-arm -avd tester -kernel ucore.elf -no-window -qemu -serial stdio

clean:
	-rm *.o
	-rm *.elf
