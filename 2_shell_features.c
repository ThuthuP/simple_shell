#include "shell.h"
/**
 * exe_command - Execute the given command.
 * @input: The  command to execute
 */
void exe_command(char *input)
{
	char *args[MAX_BUFFER_SIZE];
	int i;

	args[0] = strtok(input, " ");

	for (i = 1; i < MAX_BUFFER_SIZE - 1; i++)
	{
		args[i] == strtok(NULL, " ");
		if (args[i] == NULL)
		{
			args[i] = NULL;
			break;
		}
	}
	pid_t child = fork();

	if (child == -1)
	{
		perror("fork");
		return;
	}
	else if (child == 0)
	{
		execve(args[0], args, environ);
		char error_message[] = "No such file or directory\n";

		write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
		_exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(child, &status, 0);
	}
}
/**
 * main - Entry point.
 *
 * Return: 0 (success)
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_size;

	while (1)
	{
		write(STDOUT_FILENO, "😊 ", 6);
		read_size = getline(&input, &input_size, stdin);
		if (read_size == -1)
		{
			write(STDOUT_FILENO, "\nGoodbye!\n", 10);
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		exe_command(input);
	}
	free(input);
	return (0);
}
