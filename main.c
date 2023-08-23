#include "shell.h"
/**
 * main - Entry point.
 *
 * Return: 0 (success)
 */
int main(void)
{
	int exec_ret;

	while (1)
	{
		fputs("$", stdout);

		input = read_input();

		if (input == NULL)
		{

			cleanup_and_exit(EXIT_SUCCESS);
		}

		if (strlen(input) > 0 && !is_blank(input) && input[0] != '|')
		{
			char *linecopy = strdup(input);

			struct commands *commands =
				parse_commands_with_pipes(input);


			if (commands->cmd_count > 1
			    || !is_history_command(input))
				add_to_history(linecopy);

			free(linecopy);
			exec_ret = exec_commands(commands);
			cleanup_commands(commands);
		}

		free(input);


		if (exec_ret == -1)
			break;
	}


	cleanup_and_exit(EXIT_SUCCESS);
	return (0);
}
