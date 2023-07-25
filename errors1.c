#include "shell.h"

/**
 * _erratoi -This Function converts a string to an integer
 * @s:This parameter string to be converted
 * Return: 0, converted number otherwise
 * -1 on error
 */
	int _erratoi(char *s)
{
		int index = 0;
		unsigned long int my_res = 0;

		if (*s == '+')
			s++;  /* TODO: why does this make main return 255? */
		for (index = 0; s[index] != '\0'; index++)
		{
			if (s[index] >= '0' && s[index] <= '9')
			{
				my_res *= 10;
				my_res += (s[index] - '0');
				if (my_res > INT_MAX)
					return (-1);
			}
			else
				return (-1);
		}
		return (my_res);

}

/**
 * print_error -This Function prints an error message
 * @info:This parameter & return info struct
 * @estr:This parameter string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d -This Function prints a decimal (integer) number (base 10)
 * @input: This parameter is an  input
 * @fd:This parameter filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int loop_count, count = 0;
	unsigned int absolute_value, current_digit;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		absolute_value = -input;
		__putchar('-');
		count++;
	}
	else
		absolute_value = input;
	current_digit = absolute_value;
	for (loop_count = 1000000000; loop_count > 1; loop_count /= 10)
	{
		if (absolute_value / loop_count)
		{

			__putchar('0' + current_digit / loop_count);
			count++;
		}
		current_digit %= loop_count;
	}
	__putchar('0' + current_digit);
	count++;

	return (count);
}

/**
 * convert_number -This Function converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char neg_sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		neg_sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (neg_sign)
		*--ptr = neg_sign;
	return (ptr);
}

/**
 * remove_comments -This Function replaces first instance of '#' with '\0'
 * @buf:This parameter address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int loop_count;

	for (loop_count = 0; buf[loop_count] != '\0'; loop_count++)
		if (buf[loop_count] == '#' && (!loop_count || buf[loop_count - 1] == ' '))
		{
			buf[loop_count] = '\0';
			break;
		}
}

