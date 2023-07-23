#include "shell.h"

/**
 * make_exit - exits the shell
 * @passed_args: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if passed_args.argv_array[0] != "exit"
 */
int make_exit(var_list *passed_args)
{
	int verf_check;

	if (passed_args->argv_array[1]) /* If there is an exit arguement */
	{
		verf_check = _erratoi(passed_args->argv_array[1]);
		if (verf_check == -1)
		{
			passed_args->status = 2;
			showOff_error(passed_args, "Illegal number: ");
			_eputs(passed_args->argv_array[1]);
			_eputchar('\n');
			return (1);
		}
		passed_args->number_of_err = _erratoi(passed_args->argv_array[1]);
		return (-2);
	}
	passed_args->number_of_err = -1;
	return (-2);
}

/**
 * ask_help - changes the current directory of the process
 * @passed_args: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int ask_help(var_list *passed_args)
{
	char **arg_array;

	arg_array = passed_args->argv_array;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}


/**
 * change_dir - changes the current directory of the process
 * @passed_args: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int change_dir(var_list *passed_args)
{
	char *str, *directory, buffer[1024];
	int ch_return;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!passed_args->argv_array[1])
	{
		directory = _getenv(passed_args, "HOME=");
		if (!directory)
			ch_return = /* TODO: what should this be? */
				chdir((directory = _getenv(passed_args, "PWD=")) ? directory : "/");
		else
			ch_return = chdir(directory);
	}
	else if (_strcmp(passed_args->argv_array[1], "-") == 0)
	{
		if (!_getenv(passed_args, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(passed_args, "OLDPWD=")), _putchar('\n');
		ch_return = /* TODO: what should this be? */
			chdir((directory = _getenv(passed_args, "OLDPWD=")) ? directory : "/");
	}
	else
		ch_return = chdir(passed_args->argv_array[1]);
	if (ch_return == -1)
	{
		showOff_error(passed_args, "can't cd to ");
		_eputs(passed_args->argv_array[1]), _eputchar('\n');
	}
	else
	{
		_setenv(passed_args, "OLDPWD", _getenv(passed_args, "PWD="));
		_setenv(passed_args, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

