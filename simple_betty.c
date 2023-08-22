#include "shell.h"

void print_string(int fd, const char *str)
{
    write(fd, str, strlen(str));
}
int main(void) {
    char input[MAX_BUFFER_SIZE]; int i;

    while (1) {
       print_string(STDOUT_FILENO, "$ ");
        ssize_t input_length = read(STDIN_FILENO, input, sizeof(input));
        
        if (input_length == -1) { perror("read"); exit(EXIT_FAILURE); }
        else if (input_length == 0) { print_string(STDOUT_FILENO, "\n"); break; }
        
        if (input[input_length - 1] == '\n') input[input_length - 1] = '\0';
        if (strcmp(input, "exit") == 0) break;
        
        char *arguments[MAX_BUFFER_SIZE / 2 + 1]; int arg_count = 0;
        
        char *token = strtok(input, " ");
        while (token != NULL) { arguments[arg_count++] = strdup(token); token = strtok(NULL, " "); }
        arguments[arg_count] = NULL;
        
        char full_path[MAX_BUFFER_SIZE];
        if (!find_command(arguments[0], full_path, sizeof(full_path))) {
            print_string(STDOUT_FILENO, "No such file or directory\n"); continue;
        }
        
        pid_t child_pid = fork();
        if (child_pid == -1) { perror("fork"); exit(EXIT_FAILURE); }
        else if (child_pid == 0) {
            execv(full_path, arguments); perror("execv"); exit(EXIT_FAILURE);
        } else {
            int status; waitpid(child_pid, &status, 0);
            for (i = 0; i < arg_count; ++i) free(arguments[i]);
        }
    }

    return 0;
}
