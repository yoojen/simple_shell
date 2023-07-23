#include "shell.h"


/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}

/**
 * input_buf - buffers chained commands
 * @passed_args: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(var_list *passed_args, char **buffer, size_t *length)
{
	ssize_t ren = 0;
	size_t len_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*buffFree((void **)passed_args->command_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if GETLINE_USAGE
		ren = getline(buffer, &len_p, stdin);
#else
		ren = _getline(passed_args, buffer, &len_p);
#endif
		if (ren > 0)
		{
			if ((*buffer)[ren - 1] == '\n')
			{
				(*buffer)[ren - 1] = '\0'; /* remove trailing newline */
				ren--;
			}
			passed_args->flagOfLine = 1;
			getRidOfComment(*buffer);
			return_history_listFr(passed_args, *buffer, passed_args->hist_len++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*length = ren;
				passed_args->command_buffer = buffer;
			}
		}
	}
	return (ren);
}

/**
 * allow_input_fr - gets a line minus the newline
 * @passed_args: parameter struct
 *
 * Return: bytes read
 */
ssize_t allow_input_fr(var_list *passed_args)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, my_len;
	ssize_t ren = 0;
	char **buf_p = &(passed_args->argument), *p;

	_putchar(FLUSH_BUFFER);
	ren = input_buf(passed_args, &buf, &my_len);
	if (ren == -1) /* EOF */
		return (-1);
	if (my_len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		checkFor_Bchain(passed_args, buf, &j, i, my_len);
		while (j < my_len) /* iterate to semicolon or end */
		{
			if (return_is_chain(passed_args, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= my_len) /* reached end of buffer? */
		{
			i = my_len = 0; /* reset position and length */
			passed_args->command_buffer_type = COMMAND_NORMAL;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (ren); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @passed_args: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(var_list *passed_args, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(passed_args->r_fd, buf, BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @passed_args: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(var_list *passed_args, char **ptr, size_t *length)
{
	static char buf[BUFFER_SIZE];
	static size_t i, my_len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == my_len)
		i = my_len = 0;

	r = read_buf(passed_args, buf, &my_len);
	if (r == -1 || (r == 0 && my_len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : my_len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


