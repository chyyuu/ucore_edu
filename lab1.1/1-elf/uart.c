
void uart_putchar(char c)
{
	*(int *)0xff012000 = c;

	return;
}
