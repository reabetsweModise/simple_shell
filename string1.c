#include "shell.h"

/**
 * _strcpy -This Function copies a string
 * @dest:This parameter the destination
 * @src:This parameter the source
 *
 * Return: pointer to destination
 */

char *_strcpy(char *dest, char *src)
{
	int loop_count = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[loop_count])
	{
		dest[loop_count] = src[loop_count];
		loop_count++;
	}
	dest[loop_count] = 0;
	return (dest);
}

/**
 * _strdup -This Function duplicates a string
 * @str:This parameter string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	int source_length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		source_length++;
	ret = malloc(sizeof(char) * (source_length + 1));
	if (!ret)
		return (NULL);
	for (source_length++; source_length--;)
		ret[source_length] = *--str;
	return (ret);
}

/**
 * _puts -This Function prints an input string
 * @str:This parameter the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int loop_count = 0;

	if (!str)
		return;
	while (str[loop_count] != '\0')
	{
		_putchar(str[loop_count]);
		loop_count++;
	}
}

/**
 * _putchar -This Function writes the character c to stdout
 * @c:This parameter character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int loop_count;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || loop_count >= WRITE_BUF_SIZE)
	{
		write(1, buf, loop_count);
		loop_count = 0;
	}
	if (c != BUF_FLUSH)
		buf[loop_count++] = c;
	return (1);
}

