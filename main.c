#include "shell.h"
/**
 * main - Entry point.
 *
 * Return: 0( success).
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t read;
const char *error_msg = "hsh: command not found: ";
while (1)
{
prompt_user();
read = getline(&line, &len, stdin);
if (read == -1)
{
if (feof(stdin))
{
write(STDOUT_FILENO, "\n", 1);
break;
}
perror("getline");
exit(EXIT_FAILURE);
}
if (line[read - 1] == '\n')
line[read - 1] = '\0';
pid_t pid = fork();
if (pid == -1)
{perror("fork");
exit(EXIT_FAILURE);}
else if (pid == 0)
{
char *token = strtok(line, " ");
if (!token)
continue;
execve(token, &token, NULL);
write(STDERR_FILENO, error_msg, strlen(error_msg));
write(STDERR_FILENO, token, strlen(token));
write(STDERR_FILENO, "\n", 1);
exit(EXIT_FAILURE);
}
else
{int status;
waitpid(pid, &status, 0);
}
}
free(line);
return (0);
}
