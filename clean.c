#include "shell.h"
/**
 * cleanup_commands - Frees up memory for the commands
 * @cmds: to be freed
 */
void cleanup_commands(struct commands *cmds)
{
	int i;

	for (i = 0; i < cmds->cmd_count; i++)
		free(cmds->cmds[i]);

	free(cmds);
}
