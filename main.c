#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

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
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            char *token = strtok(line, " ");
	    if(!token)
		   continue;
            execve(token, &token, NULL);

            // If execve fails, print error message
            const char *error_msg = "hsh: command not found: ";
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            write(STDERR_FILENO, token, strlen(token));
            write(STDERR_FILENO, "\n", 1);
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}

