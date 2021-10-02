#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;

	init_env_list(env);
	while (1)
	{
		if (!(line = readline("ader$>")))
	    	return (1);
		expander(line);
	}
	return (0);
}