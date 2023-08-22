#include "shell.h"
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

