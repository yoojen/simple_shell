#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char ch)
{
	static int i;
	static char buf[NW_BUFFER_SIZE];

	if (ch == FLUSH_BUFFER || i >= NW_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != FLUSH_BUFFER)
		buf[i++] = ch;
	return (1);
}

/**
 * _putfile - writes the character c to given fd
 * @c: The character to print
 * @my_file: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfile(char c, int my_file)
{
	static int i;
	static char buf[NW_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= NW_BUFFER_SIZE)
	{
		write(my_file, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfile - prints an input string
 * @str: the string to be printed
 * @file: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfile(char *str, int file)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfile(*str++, file);
	}
	return (j);
}

