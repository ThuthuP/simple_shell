#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


/**
 * print_string - Writes a string to a file descriptor.
 * @fd: The file descriptor to write to.
 * @str: The string to be written.
 */
void print_string(int fd, const char *str);

/**
 * find_command - Finds the full path of the command using the PATH environment variable.
 * @command: The command to find.
 * @full_path: The buffer to store the full path of the command.
 * @buffer_size: The size of the full_path buffer.
 * @return: Returns 1 if found, 0 if not found.
 */
int find_command(const char *command, char *full_path, size_t buffer_size);

int main(void)
{
    char input[MAX_BUFFER_SIZE];

    while (1)
    {
        // Display prompt
        print_string(STDOUT_FILENO, "simple_shell> ");

        // Read user input
        ssize_t input_length = read(STDIN_FILENO, input, sizeof(input));
        if (input_length == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        else if (input_length == 0)
        {
            // End of file (Ctrl+D)
            print_string(STDOUT_FILENO, "\n");
            break;
        }

        // Remove newline character
        if (input[input_length - 1] == '\n')
        {
            input[input_length - 1] = '\0';
        }

        // Check for built-in commands
        if (strcmp(input, "exit") == 0)
        {
            // Exiting the shell
            print_string(STDOUT_FILENO, "Exiting shell.\n");
            break;
        }

        // Tokenize the input into arguments
        char *arguments[MAX_BUFFER_SIZE / 2 + 1]; // Maximum arguments possible
        int arg_count = 0;

        char *token = strtok(input, " ");
        while (token != NULL)
        {
            arguments[arg_count++] = strdup(token);
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL;

        // Find the full path of the command
        char full_path[MAX_BUFFER_SIZE];
        if (!find_command(arguments[0], full_path, sizeof(full_path)))
        {
            print_string(STDOUT_FILENO, "No such file or directory\n");
            continue;
        }

        // Fork a child process
        pid_t child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (child_pid == 0)
        {
            // Child process

            // Execute the input as a command
            execv(full_path, arguments);

            // If execv returns, there was an error
            perror("execv");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            int status;
            waitpid(child_pid, &status, 0);
        }

        // Free allocated memory for arguments
        for (int i = 0; i < arg_count; ++i)
        {
            free(arguments[i]);
        }
    }

    return 0;
}

void print_string(int fd, const char *str)
{
    write(fd, str, strlen(str));
}

int find_command(const char *command, char *full_path, size_t buffer_size)
{
    // Get the PATH environment variable
    const char *path = getenv("PATH");
    if (path == NULL)
    {
        return 0; // PATH is not set
    }
 if (command[0] == '/')
    {
        // Command is already an absolute path
        if (access(command, X_OK) == 0)
        {
            strncpy(full_path, command, buffer_size - 1);
            full_path[buffer_size - 1] = '\0';
            return 1;
        }
        return 0;
    }

    // Tokenize the PATH to find the command
    char path_copy[MAX_BUFFER_SIZE];
    strncpy(path_copy, path, sizeof(path_copy) - 1);
    path_copy[sizeof(path_copy) - 1] = '\0';

    int found = 0;
    char *dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        int dir_len = strlen(dir);
        int command_len = strlen(command);
        if (dir_len + command_len + 2 <= buffer_size) // +2 for '/' and null terminator
        {
            strcpy(full_path, dir);
            full_path[dir_len] = '/';
            strcpy(full_path + dir_len + 1, command);

            if (access(full_path, X_OK) == 0)
            {
                found = 1;
                break;
            }
        }
        dir = strtok(NULL, ":");
    }

    return found;
}
