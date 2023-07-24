#include "shell.h"

/**
 **_strncpy -This Function copies a string
 *@dest:This parameter destination string to be copied to
 *@src:This parameter source string
 *@n:This parameter amount of characters to be copied
 *Return:This parameter concatenated string
 */
	char *_strncpy(char *dest, char *src, int n)
{
	int first_counter, second_counter;
	char *s = dest;

	first_counter = 0;
	while (src[first_counter] != '\0' && first_counter < n - 1)
	{
		dest[first_counter] = src[first_counter];
		first_counter++;
	}
	if (first_counter < n)
	{
		second_counter = first_counter;
		while (second_counter < n)
		{
			dest[second_counter] = '\0';
			second_counter++;
		}
	}
	return (s);
}

/**
 **_strncat -This Function concatenates two strings
 *@dest:This parameter  first string
 *@src:This parameter second string
 *@n:This parameter amount of bytes to be maximally used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int first_counter, second_counter;
	char *s = dest;

	first_counter = 0;
	second_counter = 0;
	while (dest[first_counter] != '\0')
		first_counter++;
	while (src[second_counter] != '\0' && second_counter < n)
	{
		dest[first_counter] = src[second_counter];
		first_counter++;
		second_counter++;
	}
	if (second_counter < n)
		dest[first_counter] = '\0';
	return (s);
}

/**
 **_strchr -This Function locates a character in a string
 *@s:This parameter string to be parsed
 *@c:This parameter character to look for
 *Return: (s) a pointer to the memory
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
