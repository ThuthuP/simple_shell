/* exec_commands -  Executes a set of commands that are piped together.
 * 
 * Return: If it's a single command, it simply calls `exec_command` or returns 0
 */
int exec_commands(struct commands *cmds)
{
	int exec_ret;

	if (cmds->cmd_count == 1) {
		cmds->cmds[0]->fds[STDIN_FILENO] = STDIN_FILENO;
		cmds->cmds[0]->fds[STDOUT_FILENO] = STDOUT_FILENO;
		exec_ret = exec_command(cmds, cmds->cmds[0], NULL);
		wait(NULL);
	} else
	{
		int pipe_count = cmds->cmd_count - 1;
		int i;

		for (i = 0; i < cmds->cmd_count; i++)
		{
			if (check_built_in(cmds->cmds[i]))
			{
				fprintf(stderr, "error: no builtins in pipe\n");
				return 0;
			}

		}
		int (*pipes)[2] = calloc(pipe_count * sizeof(int[2]), 1);

		if (pipes == NULL)
		{
			fprintf(stderr, "error: memory alloc error\n");
			return (0);
		}
		cmds->cmds[0]->fds[STDIN_FILENO] = STDIN_FILENO;
		for (i = 1; i < cmds->cmd_count; i++)
		{
			pipe(pipes[i-1]);
			cmds->cmds[i-1]->fds[STDOUT_FILENO] = pipes[i-1][1];
			cmds->cmds[i]->fds[STDIN_FILENO] = pipes[i-1][0];
		}
		cmds->cmds[pipe_count]->fds[STDOU_FILENO] = STDOUT_FILENO;
		for (i = 0; i < cmds->cmd_count; i++)
			exec_ret = exec_command(cmds, cmds->cmds[i], pipes);
		close_pipes(pipes, pipe_count);
		for (i = 0; i < cmds->cmd_count; ++i)
			wait(NULL);

		free(pipes);
	}

	return (exec_ret);
}
