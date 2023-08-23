#include "shell.h"
/**
 * read_input - read input entered by the user.
 *
 * Return: a pointer to a input entered by user.
 * the caller is responsible for freeing up the memory
 */
char *read_input(void)
{
	int buffer_size = 2048;
	char *input = malloc(buffer_size * sizeof(char));
	int i = 0;
	char c;

	if (input == NULL)
	{
		fprintf(stderr, "error: malloc failed\n");
		cleanup_and_exit(EXIT_FAILURE);
	}

	while ((c = getchar()) != '\n')
	{
		/* did user enter ctrl+d ?*/
		if (c == EOF)
		{
			free(input);
			return (NULL);
		}

		/* allocate more memory for input */
		if (i >= buffer_size)
		{
			buffer_size = 2 * buffer_size;
			input = realloc(input, buffer_size);
		}

		input[i++] = c;
	}

	input[i] = '\0';
	return (input);
}
