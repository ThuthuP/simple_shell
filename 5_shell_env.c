#include "shell.h"

/**
 * search_executable -Search for the executable in PATH
 * @command: The command to search for
 *
 * Return: The full path of the executable if found, or NULL if not found
 */

char *search_executable(char *command)
{
}

/**
 * print_enviroment - print the currant enviroment variables
 */

void print_enviroment(void)
{
for (char **env = environ; *env != NULL; env++)
{
write(STDOUT_FILENO, *env, strlen(*env));
write(STDOUT_FILENO, "\n", 1);
}
}
char *input = NULL;
size_t input_size = 0;
while (1)
{
write(STOUT_FILENO, "😊 ", 4);
ssize_t read_size = getline(&input, &input_size, stdin);
if (read_size == -1)
{
write(STOUT_FILE, "\nGoodbye!\n", 10);
break;
}
input[strcspn(input, "\n")] = '\0';
if (strcspn(input, "exit") == 0)
{
write(STDOUT_FILENO, "Exiting the Smile Shell!\n",
26);
break;
}
else if (strcmp(input, "env") == 0)
{
print_enviroment();
}
else
{
char *executable_path = search_executable(input);
if (executable_path == NULL)
{
char error_msg[] = "Command not found\n";
write(STDERR_FILENO, error_msg,
sizeof(error_msg) - 1);
}
else
{
}
free(executable_path);
}
}
free(input);
return (0);
}
