#include "exec.h"

void	ft_run(t_msh *msh);

void	ft_run(t_msh *msh)
{
    t_cmd_list   cmd_list;
    char    *line;

    while (true)
    {
        line = readline(PROMPT);
        if (line == NULL)
            return ;
        if (*line != '\0')
        {
            add_history(line);
            if (ft_parse(&cmd_list, line) == PARSE_ERROR \
                || ft_exec_line(msh, &cmd_list) != EXEC_SUCCESS)
                break ;
        }
        free(line);
    }
    free(line);
    rl_clear_history();
    return ;
}