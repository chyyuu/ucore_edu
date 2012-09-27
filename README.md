ucore_edu
=========

Operating System Design and Implementation with uCore

## lab1.0
build dev enviroment

	install arm-eabi-gcc
		tar zxvf arm-eabi-gcc-4.6-linux-x86.tar.gz

	install android-sdk-linux
		tar zxvf androidsdk-4.1.tar.gz

## lab1.1 
ucore with uart print message

	entry.S -> init.c
	-------------------
		   stdio.c
	-------------------
		   uart.c


## lab1.2

	entry.S -> init.c 	vector.S
	--------------------------------------
		   stdio.c
	--------------------------------------
		   uart.c	interrupt.c

	

