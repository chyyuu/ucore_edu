

.global init

.section .text
.global _start
_start:
	ldr sp, =0x1000
	b init
