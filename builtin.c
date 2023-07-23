#include "shell.h"


/**
 * bool_delimiter - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int bool_delimiter(char ch, char *d)
{
	while (*d)
		if (*d++ == ch)
			return (1);
	return (0);
}
/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
 
 /**
 * interactive - returns true if shell is interactive mode
 * @passed_args: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(var_list *passed_args)
{
	return (isatty(STDIN_FILENO) && passed_args->r_fd <= 2);
}

int _atoi(char *s)
{
	unsigned int rs = 0;
	int i, sign = 1, fl = 0, ret;

	for (i = 0; s[i] != '\0' && fl != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			fl = 1;
			rs *= 10;
			rs += (s[i] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (sign == -1)
		ret = -rs;
	else
		ret = rs;

	return (ret);
}

/**
 * _isalpha - checks for alphabetic character
 * @ch: The character to input
 * Return: 1 if ch is alphabetic, 0 otherwise
 */

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}


