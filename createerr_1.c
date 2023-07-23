#include "shell.h"


/**
 * showOff_error - prints an error message
 * @passed_args: the parameter & return passed_args struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void showOff_error(var_list *passed_args, char *strings)
{
	_eputs(passed_args->file_name);
	_eputs(": ");
	printDError(passed_args->number_of_line, STDERR_FILENO);
	_eputs(": ");
	_eputs(passed_args->argv_array[0]);
	_eputs(": ");
	_eputs(strings);
}

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *str)
{
	unsigned long int res = 0;
	int i = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}


/**
 * printDError - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @file: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int printDError(int input, int file)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absoulut, curr;

	if (file == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		absoulut = -input;
		__putchar('-');
		count++;
	}
	else
		absoulut = input;
	curr = absoulut;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absoulut / i)
		{
			__putchar('0' + curr / i);
			count++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * getRidOfComment - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void getRidOfComment(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

/**
 * conversationof_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @fl: argument fl
 *
 * Return: string
 */
char *conversationof_number(long int num, int bs, int fl)
{
	static char *arrayOfnumber;
	static char buffer[50];
	char outSign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(fl & UNSIGNED_CONVERTER) && num < 0)
	{
		n = -num;
		outSign = '-';

	}
	arrayOfnumber = fl & LOWER_CONVERTER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arrayOfnumber[n % bs];
		n /= bs;
	} while (n != 0);

	if (outSign)
		*--ptr = outSign;
	return (ptr);
}


