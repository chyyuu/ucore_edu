
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
