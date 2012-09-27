
int putchar(int c)
{
	uart_putchar(c);

	return;
}

int puts(const char * s)
{
	while (*s)
		putchar(*s++);

	return 0;
}
