#include "shell.h"

/**
 * is_It_command - determines if a file is an executable command
 * @passed_args: the passed_args struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_It_command(var_list *passed_args, char *lfile_path)
{
	struct stat st;

	(void)passed_args;
	if (!lfile_path || stat(lfile_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * make_duplication - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *make_duplication(char *pathstr, int index_zero, int end_index)
{
	static char buffer[1024];
	int i = 0, h = 0;

	for (h = 0, i = index_zero; i < end_index; i++)
		if (pathstr[i] != ':')
			buffer[h++] = pathstr[i];
	buffer[h] = 0;
	return (buffer);
}

/**
 * return_pathname - finds this cmd in the PATH string
 * @passed_args: the passed_args struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *return_pathname(var_list *passed_args, char *str_path, char *command)
{
	int i = 0, current_position = 0;
	char *ret_path;

	if (!str_path)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_It_command(passed_args, command))
			return (command);
	}
	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			ret_path = make_duplication(str_path, current_position, i);
			if (!*ret_path)
				_strcat(ret_path, command);
			else
			{
				_strcat(ret_path, "/");
				_strcat(ret_path, command);
			}
			if (is_It_command(passed_args, ret_path))
				return (ret_path);
			if (!str_path[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}

