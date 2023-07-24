#include "shell.h"

/**
 * interactive -This Function returns true if shell is interactive mode
 * @info:This parameter  struct address
 *
 * Return: 1 , 0 otherwise
 */
	int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim -This Function checks if character is a delimeter
 * @c:This parameter  char to check
 * @delim:This parameter delimeter string
 * Return: 1 (true), 0 (false)
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha -This Function checks for alphabetic character
 * @c:This parameter character to input
 * Return: 1 , 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi -This Function converts a string to an integer
 * @s:This parameter the string to be converted
 * Return: 0 , converted number otherwise
 */

int _atoi(char *s)
{
	int index, my_sign = 1, my_flag = 0, my_output;
	unsigned int result = 0;

	for (index = 0; s[index] != '\0' && my_flag != 2; index++)
	{
		if (s[index] == '-')
			my_sign *= -1;

		if (s[index] >= '0' && s[index] <= '9')
		{
			my_flag = 1;
			result *= 10;
			result += (s[index] - '0');
		}
		else if (my_flag == 1)
			my_flag = 2;
	}

	if (my_sign == -1)
		my_output = -result;
	else
		my_output = result;

	return (my_output);

}
