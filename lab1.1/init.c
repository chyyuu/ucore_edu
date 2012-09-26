
void init(void)
{
#if 0
	*(int *)0xff012000 = 'u';
	*(int *)0xff012000 = 'c';
	*(int *)0xff012000 = 'o';
	*(int *)0xff012000 = 'r';
	*(int *)0xff012000 = 'e';

	while (1);
#endif

	puts("hello, ucore\n");

	while (1);

	return;
}
