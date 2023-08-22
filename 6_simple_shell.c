#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

/**
 * print_string - Writes a string to a file descriptor.
 * @fd: The file descriptor to write to.
 * @str: The string to be written.
 */
void print_string(int fd, const char *str);

/**
 * my_getline - Reads a line from standard input using a buffer.
 * @line: The buffer to store the line.
 * @size: The size of the buffer.
 * @return: Returns the number of characters read.
 */
ssize_t my_getline(char *line, size_t size);

int main(void) {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        // Display prompt
        print_string(STDOUT_FILENO, "simple_shell> ");

        // Read user input using custom my_getline function
        ssize_t input_length = my_getline(input, sizeof(input));
        if (input_length == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        } else if (input_length == 0) {
            // End of file (Ctrl+D)
            print_string(STDOUT_FILENO, "\n");
            break;
        }

        // Remove newline character
        if (input[input_length - 1] == '\n') {
            input[input_length - 1] = '\0';
        }

        // TODO: Process user input and execute commands
    }

    print_string(STDOUT_FILENO, "Exiting shell.\n");
    return 0;
}

void print_string(int fd, const char *str) {
    write(fd, str, strlen(str));
}

ssize_t my_getline(char *line, size_t size) {
    static char buffer[MAX_INPUT_LENGTH];
    static ssize_t position = 0;
    static ssize_t buffer_size = 0;

    ssize_t bytesRead = 0;
    while (1) {
        if (position >= buffer_size) {
            // Read more data into buffer
            buffer_size = read(STDIN_FILENO, buffer, sizeof(buffer));
            if (buffer_size <= 0) {
                return bytesRead; // Return total bytes read
}
position = 0;
}
char c = buffer[position++];
if (c == '\n' || bytesRead == size - 1) {
line[bytesRead] = '\0';
return bytesRead;
}
line[bytesRead++] = c;
}
}
