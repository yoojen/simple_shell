#include "shell.h"

/**
 * **my_strtok_1 - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **my_strtok_1(char *str, char *d)
{
	int i, j, h, m, numberOFfWords = 0;
	char **ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!bool_delimiter(str[i], d) && (bool_delimiter(str[i + 1], d) || !str[i + 1]))
			numberOFfWords++;

	if (numberOFfWords == 0)
		return (NULL);
	ptr = malloc((1 + numberOFfWords) * sizeof(char *));
	if (!ptr)
		return (NULL);
	for (i = 0, j = 0; j < numberOFfWords; j++)
	{
		while (bool_delimiter(str[i], d))
			i++;
		h = 0;
		while (!bool_delimiter(str[i + h], d) && str[i + h])
			h++;
		ptr[j] = malloc((h + 1) * sizeof(char));
		if (!ptr[j])
		{
			for (h = 0; h < j; h++)
				free(ptr[h]);
			free(ptr);
			return (NULL);
		}
		for (m = 0; m < h; m++)
			ptr[j][m] = str[i++];
		ptr[j][m] = 0;
	}
	ptr[j] = NULL;
	return (ptr);
}

/**
 * **my_strtok_2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **my_strtok_2(char *str, char d)
{
	char **str_hold;
	int i, j, h, m, numberOfWords = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numberOfWords++;
	if (numberOfWords == 0)
		return (NULL);
	str_hold = malloc((1 + numberOfWords) * sizeof(char *));
	if (!str_hold)
		return (NULL);
	for (i = 0, j = 0; j < numberOfWords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		h = 0;
		while (str[i + h] != d && str[i + h] && str[i + h] != d)
			h++;
		str_hold[j] = malloc((h + 1) * sizeof(char));
		if (!str_hold[j])
		{
			for (h = 0; h < j; h++)
				free(str_hold[h]);
			free(str_hold);
			return (NULL);
		}
		for (m = 0; m < h; m++)
			str_hold[j][m] = str[i++];
		str_hold[j][m] = 0;
	}
	str_hold[j] = NULL;
	return (str_hold);
}

