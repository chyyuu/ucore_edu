
ENTRY(_start)

SECTIONS
{
	. = 0x108000;	/* 1M + 32k */
	.text : { *(.text) }
	.data : { *(.data) }
	.bss : { *(.bss) }
}
