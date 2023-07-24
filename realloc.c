#include "shell.h"

/**
 * _memset -This Function fills memory with a constant byte
 * @s:This parameter pointer to the memory area
 * @b:This parameter byte to fill *s with
 * @n:This parameter amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int loop_count;

	for (loop_count = 0; loop_count < n; loop_count++)
		s[loop_count] = b;
	return (s);
}

/**
 * ffree -This Function frees a string of strings
 * @pp:This parameter string of strings
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc -This Function reallocates a block of memory
 * @ptr:This parameter pointer to previous malloc'ated block
 * @old_size:This parameter byte size of previous block
 * @new_size:This parameter byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

