#include "shell.h"

/**
 * strtow -This Function splits a string into words.
 * Repeat delimiters are ignored
 * @str:This parameter the input string
 * @d:This parameter delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */


char **strtow(char *str, char *d)
{
	int loop_count_1, loop_count_2, char_in_word, loop_count_3,
	    words_in_string = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (loop_count_1 = 0; str[loop_count_1] != '\0'; loop_count_1++)
		if (!is_delim(str[loop_count_1], d) &&
				(is_delim(str[loop_count_1 + 1], d) ||
				 !str[loop_count_1 + 1]))
			words_in_string++;
	if (words_in_string == 0)
		return (NULL);
	s = malloc((1 + words_in_string) * sizeof(char *));
	if (!s)
		return (NULL);
	for (loop_count_1 = 0, loop_count_2 = 0; loop_count_2 < words_in_string;
			loop_count_2++)
	{
		while (is_delim(str[loop_count_1], d))
			loop_count_1++;
		char_in_word = 0;
		while (!is_delim(str[loop_count_1 + char_in_word], d) &&
				str[loop_count_1 + char_in_word])
			char_in_word++;
		s[loop_count_2] = malloc((char_in_word + 1) * sizeof(char));
		if (!s[loop_count_2])
		{
			for (char_in_word = 0; char_in_word < loop_count_2; char_in_word++)
				free(s[char_in_word]);
			free(s);
			return (NULL);
		}
		for (loop_count_3 = 0; loop_count_3 < char_in_word; loop_count_3++)
			s[loop_count_2][loop_count_3] = str[loop_count_1++];
		s[loop_count_2][loop_count_3] = 0;
	} s[loop_count_2] = NULL;
	return (s);
}

/**
 * strtow2 -This Function splits a string into words
 * @str:This parameter input string
 * @d:This parameter delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow2(char *str, char d)
{
	int loop_count_1, loop_count_2, char_in_word,
	    loop_count_3, words_in_string = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (loop_count_1 = 0; str[loop_count_1] != '\0'; loop_count_1++)
		if ((str[loop_count_1] != d && str[loop_count_1 + 1] == d) ||
			(str[loop_count_1] != d && !str[loop_count_1 + 1]) ||
			str[loop_count_1 + 1] == d)
			words_in_string++;
	if (words_in_string == 0)
		return (NULL);
	s = malloc((1 + words_in_string) * sizeof(char *));
	if (!s)
		return (NULL);
	for (loop_count_1 = 0, loop_count_2 = 0; loop_count_2 < words_in_string;
			loop_count_2++)
	{
		while (str[loop_count_1] == d && str[loop_count_1] != d)
			loop_count_1++;
		char_in_word = 0;
		while (str[loop_count_1 + char_in_word] != d &&
				str[loop_count_1 + char_in_word] &&
				str[loop_count_1 + char_in_word] != d)
			char_in_word++;
		s[loop_count_2] = malloc((char_in_word + 1) * sizeof(char));
		if (!s[loop_count_2])
		{
			for (char_in_word = 0; char_in_word < loop_count_2; char_in_word++)
				free(s[char_in_word]);
			free(s);
			return (NULL);
		}
		for (loop_count_3 = 0; loop_count_3 < char_in_word; loop_count_3++)
			s[loop_count_2][loop_count_3] = str[loop_count_1++];
		s[loop_count_2][loop_count_3] = 0;
	}
	s[loop_count_2] = NULL;
	return (s);
}

