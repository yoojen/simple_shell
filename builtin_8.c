#include "shell.h"

/**
 * dispayFilehistory - creates a file, or appends to an existing file
 * @passed_args: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int dispayFilehistory(var_list *passed_args)
{
	ssize_t fd;
	char *filename = history_of_file_returns(passed_args);
	my_list *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = passed_args->history; node; node = node->next)
	{
		_putsfile(node->str, fd);
		_putfile('\n', fd);
	}
	_putfile(FLUSH_BUFFER, fd);
	close(fd);
	return (1);
}


/**
 * history_of_file_returns - gets the history file
 * @passed_args: parameter struct
 *
 * Return: allocated string containg history file
 */

char *history_of_file_returns(var_list *passed_args)
{
	char *buffer, *directory_;

	directory_ = _getenv(passed_args, "HOME=");
	if (!directory_)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory_) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory_);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * nread_history_infos - reads history from file
 * @passed_args: the parameter struct
 *
 * Return: hist_len on success, 0 otherwise
 */
int nread_history_infos(var_list *passed_args)
{
	int i, last = 0, number_lines = 0;
	ssize_t files, _rdlength, file_size = 0;
	struct stat st;
	char *buf = NULL, *filename = history_of_file_returns(passed_args);

	if (!filename)
		return (0);

	files = open(filename, O_RDONLY);
	free(filename);
	if (files == -1)
		return (0);
	if (!fstat(files, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);
	_rdlength = read(files, buf, file_size);
	buf[file_size] = 0;
	if (_rdlength <= 0)
		return (free(buf), 0);
	close(files);
	for (i = 0; i < file_size; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			return_history_listFr(passed_args, buf + last, number_lines++);
			last = i + 1;
		}
	if (last != i)
		return_history_listFr(passed_args, buf + last, number_lines++);
	free(buf);
	passed_args->hist_len = number_lines;
	while (passed_args->hist_len-- >= HIST_MAX)
		delete_node_at_An_index(&(passed_args->history), 0);
	numberHistory(passed_args);
	return (passed_args->hist_len);
}


/**
 * numberHistory - renumbers the history linked list after changes
 * @passed_args: Structure containing potential arguments. Used to maintain
 *
 * Return: the new hist_len
 */
int numberHistory(var_list *passed_args)
{
	my_list *node = passed_args->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (passed_args->hist_len = i);
}

/**
 * return_history_listFr - adds entry to a history linked list
 * @passed_args: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @line_numbered: the history linecount, hist_len
 *
 * Return: Always 0
 */
int return_history_listFr(var_list *passed_args, char *buf, int line_numbered)
{
	my_list *node = NULL;

	if (passed_args->history)
		node = passed_args->history;
	add_node_at_end(&node, buf, line_numbered);

	if (!passed_args->history)
		passed_args->history = node;
	return (0);
}


