#include "shell.h"
/**
 * main - Entry point
 *
 * Return: 0 (success)
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;

	while (1)
	{
		write(STDOUT_FILENO, "😊 ", 6);
		ssize_t read_size = getline(&input, &input_size, stdin);

		if (read_size == -1)
		{
			write(STDOUT_FILENO, "\nGoodbye!\n", 10);
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		pid_t child = fork();

		if (child == -1)
		{
			perror("fork");
			continue;
		}
		else if (child == 0)
		{
			char *args[] = {input, NULL};

		execve(input, args, environ);
		char error_message[] = "No such file or directory\n";

		write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
		}
		else
		{
			int status;

			waitpid(child, &status, 0);
		}
	}
	free(input);
	return (0);
}
