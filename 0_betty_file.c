#include "shell.h"
/**
 * fly_drone - Simulate drone flight.
 *
 */
void fly_drone(void)
{
	const char *launch = "Drone launching!\n";
	const char *landing = "Drone landing!\n";

	write(STDOUT_FILENO, launch, strlen(launch));
	sleep(4);
	write(STDOUT_FILENO, landing, strlen(landing));
}
/**
 * main - Entry point.
 *
 * Return: 0 (success)
 */
int main(void)
{
	pid_t child = fork();

	if (child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child == 0)
	{
		fly_drone();
		_exit(0);
	}
	else
	{
		int status;

		waitpid(child, &status, 0);
		if (status == 0)
		{
			write(STDOUT_FILENO, "Process exited.\n", strlen("Process exited.\n"));
		}
		else
		{
	write(STDOUT_FILENO, "Terminated.\n", strlen("Terminated.\n"));
		}
		write(STDOUT_FILENO, "Flight completed.\n", strlen("Flight completed.\n"));
	}
	write(STDOUT_FILENO, "Exiting program.\n", strlen("Exiting program.\n"));
	return (0);
}
