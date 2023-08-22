#include "shell.h"
/**
 * main - entry point.
 *
 * Return: 0 (success).
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_size;
	pid_t child;
	char *args[2];
	char error_message[] = "./hsh: No such file or directory\n";
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "simple_shell$ ", 15);
		read_size = getline(&input, &input_size, stdin);
		if (read_size == -1)
		{
			if (feof(stdin))
				write(STDOUT_FILENO, "\nGoodbye!\n", 10);
			else
				perror("getline");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		child = fork();
		if (child == -1)
		{
			perror("fork");
			continue;
		}
		else if (child == 0)
		{
			args[0] = input;
			args[1] = NULL;
			execve(input, args, NULL);
			write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
			_exit(EXIT_FAILURE);
		}
		else
			waitpid(child, &status, 0);
	}
	free(input);
	return (0);
}
