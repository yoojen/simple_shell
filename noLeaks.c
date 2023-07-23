#include "shell.h"

/**
 * buffFree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int buffFree(void **pontr)
{
	if (pontr && *pontr)
	{
		free(*pontr);
		*pontr = NULL;
		return (1);
	}
	return (0);
}

