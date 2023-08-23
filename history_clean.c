#include "shell.h"
/**
 * cleanup_and_exit - cleans up history before exits
 * @status: check and exit
 */
void cleanup_and_exit(int status)
{
	clear_history();
	free(history);
	exit(status);
}
