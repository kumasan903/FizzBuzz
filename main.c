typedef __UINT8_TYPE__ uint8_t;
typedef __SIZE_TYPE__ size_t;

void km_write(int fd, const void *buf, size_t count)
{
	size_t ret;
	asm
	(
		"syscall"
		: "=r" (ret)
		: "0"(1), "D"(fd), "S"(buf), "d"(count)
	);
	(void)ret;
}

size_t km_strlen(char *str)
{
	char *start;
	start = str;
	while (*str)
		*str++;
	return (str - start);
}

void km_putstr(char *str)
{
	km_write(1, str, km_strlen(str));
}

void km_putchar(int c)
{
	km_write(1, &c, 1);
}

void km_putnbr(uint8_t n)
{
	size_t divisor;
	divisor = 1;
	while ((n / divisor) >= 10)
		divisor *= 10;
	while (divisor > 0)
	{
		km_putchar((n / divisor % 10) + '0');
		divisor /= 10;
	}
	km_putchar('\n');
}

void fizz_buzz(uint8_t n)
{
	uint8_t i;
	i = 1;
	while(i <= n)
	{
		if (i % 3 == 0 && i % 5 == 0)
			km_putstr("FizzBuzz\n");
		else if(i % 3 == 0)
			km_putstr("Fizz\n");
		else if(i % 5 == 0)
			km_putstr("Buzz\n");
		else
			km_putnbr(i);
		i++;
	}
}

void main(void)
{
	fizz_buzz(100);
}
