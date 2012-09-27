#include "uart.c"
#include "stdio.c"

void putchar_hex(char c)
{
	char * hex = "0123456789ABCDEF";	// good
	
	putchar(hex[(c & 0xf0)>>4]);
	putchar(hex[(c & 0x0f)>>0]);
//	putchar(' ');
}

void putint_hex(int a)
{
	putchar_hex( (a>>24) & 0xFF );
	putchar_hex( (a>>16) & 0xFF );
	putchar_hex( (a>>8) & 0xFF );
	putchar_hex( (a>>0) & 0xFF );
}

void load_elf_from(int elf_addr)
{
	int p_ucore_off;	// load addr in elf file
	int ucore_size;		// .text section size

	int p_ucore_exec;	// exec addr to go
	int i;

	// .text is at offset 0x8000
	// 0x81b0 is read from run commmand <hexdump -C ucore.elf | grep "d0 00">
	// while "d0 00" is read from run command <readelf -a ucore.elf | grep ".text">
	// .text section header base addr
	//
	int sh_base = *(int *)(0x20 + elf_addr);

	int text_sh_base = sh_base + 0x28;	// 40 bytes for one section header 

	puts("ucore section header base addr: ");
	putint_hex(sh_base);
	putchar('\n');

	puts("ucore .text section header base addr: ");
	putint_hex(text_sh_base);
	putchar('\n');

	p_ucore_off = *(int *)(text_sh_base+0x10 + 0x1000);	
	ucore_size = *(int *)(text_sh_base+0x14 + 0x1000);
	p_ucore_exec = *(int *)(text_sh_base+0xc + 0x1000);

	puts("ucore .text offset: ");
	putint_hex(p_ucore_off);
	putchar('\n');
	puts("ucore .text size: ");
	putint_hex(ucore_size);
	putchar('\n');
	puts("ucore .text exec addr: ");
	putint_hex(p_ucore_exec);
	putchar('\n');

	// add .rodata size to loader
	ucore_size += 100;

	for (i = 0; i < ucore_size/4; i++)
		*(int *)(p_ucore_exec+i*4) = *(int *)(p_ucore_off+i*4+elf_addr);

	return;
}

int mymain(void)
{
	// ucore.elf is loaded from bootloader.elf to 0x1000
	int * p = (int *)0x1000;

	putint_hex(*p);
	puts("\n<boot> " __FILE__ "\n");
	
	puts("booting...load ucore.elf from 0x1000, put .text section to 0x108000\n");
	
	// read elf header and load .text to 0x8000 as ucore.lst indicated . = 0x8000
	load_elf_from(0x1000);

	puts("go to 0x108000 to run ucore\n");
	// run ucore at 0x108000
	((void (*)(void))0x108000)();

	while (1);

	return 0;
}
