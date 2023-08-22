#include "shell.h"
/**
 * fly_drone - Simulate drone flight
 * code to fly the drone
 */
void fly_drone(void)
{
const char *launch = "Drone launching!\n";
const char *landing = "Drone landing!\n";

write(STDOUT_FILENO, launch, strlen(launch));
sleep(5);
write(STDOUT_FILENO, landing, strlen(landing));
}

/**
 * main - entry point.
 *
 * Return: 0 success.
 */
int main(void)
{
pid_t child_pid = fork();

if (child_pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
if (child_pid == 0)
{
fly_drone();
_exit(0);
}
else
{
int status;
waitpid(child_pid, &status, 0);

if (status == 0)
{
write(STDOUT_FILENO, "exited.\n", strlen("exited.\n"));
}
else
{
write(STDOUT_FILENO, "terminated\n", strlen("terminated\n"));
}
write(STDOUT_FILENO, "flight completed.\n", strlen("flight completed.\n"));
}
write(STDOUT_FILENO, "Exiting program.\n", strlen("Exiting program.\n"));
return (0);
}
