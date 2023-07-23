#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	var_list passed_args[] = { INFO_INIT };
	int file = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file)
		: "r" (file));

	if (ac == 2)
	{
		file = open(av[1], O_RDONLY);
		if (file == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		passed_args->r_fd = file;
	}
	use_all_env_main(passed_args);
	nread_history_infos(passed_args);
	hsh(passed_args, av);
	return (EXIT_SUCCESS);
}

