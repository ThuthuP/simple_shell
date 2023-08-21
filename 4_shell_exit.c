#include "shell.h"
/**
 * search_executable - Search for an executable file in the PATH
 * @command: The command to search fo
 * Return: PATH to the executable if found, if not (NULL)
 */
char *search_executable(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char executable_path[MAX_BUFFER_SIZE];
	size_t dir_len;

	while (dir != NULL)
	{
		dir_len = strlen(dir);
		if (dir_len + strlen(command) + 2 > sizeof(executable_path))
		{
			dir = strtok(NULL, ":");
			continue;
		}
		strcpy(executable_path, dir);
		executable_path[dir_len] = '/';
		strcpy(executable_path + dir_len + 1, command);

		if (access(executable_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(executable_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
/**
 * main - Entry point.
 *
 * Return: 0 (success).
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
if (strcmp(input, "exit") == 0)
{
write(STDOUT_FILENO, "Exiting the Smile Shell!\n",
26);
break;
}
char *executable_path = search_executable(input);
if (executable_path == NULL)
{
char error_message[] = "No such file or directory\n";
write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
}
else
{
}
free(executable_path);
}
free(input);
return (0);
}
