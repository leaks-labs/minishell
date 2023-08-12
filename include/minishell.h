#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

# define PROMPT "minishell$ "

#endif