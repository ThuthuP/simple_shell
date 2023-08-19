#include "shell.h"

/*
 * main - entry point
 * print_string - writes a string to a file descriptor
 * Return value : Return value must be always (0)
 */

char *input = NULL;
size_t input_size = 0;
while (1)
{
write(STDOUT_FILENO, "😊 ", 4);
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
char *executable_pah = search_executable(input);
if (executable_path == NULL)
{
char error_msg[] = "Command not found\n";
write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
}
else
{
}
free(executable_path);
}
free(input);
return (0);
}
