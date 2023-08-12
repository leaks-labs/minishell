#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*text;

	(void)argc;
	(void)argv;
	(void)envp;
	text = readline(PROMPT);
	while (text != NULL)
	{
		if (*text != '\0')
			add_history(text);
		if (*text != '\0')
			printf("%s\n", text);
		free(text);
		text = readline(PROMPT);
	}
	free(text);
	rl_clear_history();
	return (0);
}