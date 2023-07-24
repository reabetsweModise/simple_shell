#include "shell.h"

/**
 * bfree -This Function frees a pointer and NULLs the address
 * @ptr:This parameter address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

