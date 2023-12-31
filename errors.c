#include "shell.h"

/**
 * _eputs -This Function prints an input string
 * @str:This parameter the string to be printed
 *
 * Return: Nothing
 */
	void _eputs(char *str)
{
		int index = 0;

		if (!str)
			return;
		while (str[index] != '\0')
		{
			_eputchar(str[index]);
			index++;
		}

}

/**
 * _eputchar -This Function writes the character c to stderr
 * @c:This parameter character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 * _putfd -This Function writes the character c to given fd
 * @c:This parameter character to print
 * @fd:This parameter  filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;

	return (1);
}

/**
 * _putsfd -This Function prints an input string
 * @str:This parameter string to be printed
 * @fd:This parameter filedescriptor to write to
 *
 * Return:chars put
 */
int _putsfd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += _putfd(*str++, fd);
	}
	return (index);
}
