#include "shell.h"

/**
 * prompt_user - prints $ to let the user know the program is
 * ready to take their input
 * prints the prompt if the shell is in interactive mode
 * Return: no return
 */
void prompt_user(void)
{
	if (isatty(STDIN_FILENO) == 1 && isatty(STDOUT_FILENO) == 1)
		write(STDOUT_FILENO, "$ ", 2);
}
