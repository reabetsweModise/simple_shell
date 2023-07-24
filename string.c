#include "shell.h"

/**
 * _strlen -This Function returns the length of a string
 * @s:This parameter the string whose length to check
 *
 * Return: integer length of string
 */

int _strlen(char *s)
{
	int loop_count = 0;

	if (!s)
		return (0);

	while (*s++)
		loop_count++;
	return (loop_count);
}

/**
 * _strcmp -This Function performs lexicogarphic comparison of two strangs.
 * @s1:This parameter first strang
 * @s2:This parameter second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with -This Function checks if needle starts with haystack
 * @haystack:This parameter string to search
 * @needle:This parameter substring to find
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat -This Function concatenates two strings
 * @dest:This parameter destination buffer
 * @src:This parameter source buffer
 *
 * Return: pointer to destination buffer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

