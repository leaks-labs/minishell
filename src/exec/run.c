#include "minishell.h"

int ft_run(t_msh *msh);

int ft_run(t_msh *msh)
{
    t_cmd cmd;
    char *line;

    while (true)
    {
        line = readline(PROMPT);
        if (line == NULL)
            return (RUN_ERROR);
        if (*line != '\0')
        {
            add_history(line);
            if (ft_parse(&cmd, line) == PARSE_ERROR)
            {
                free(line);
                rl_clear_history();
                return (RUN_ERROR);
            }
            if (ft_exec_line(msh, &cmd) != EXEC_SUCCESS)
                break;
        }
        free(line);
    }
    free(line);
    rl_clear_history();
    return (RUN_SUCCESS);
}