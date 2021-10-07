#include "minishell.h"

char	*make_string(char *str, char c)
{
	int		i;
	char	*p;
	i = 0;
	
	if (str == NULL)
	{
		p = strdup("");
		return (make_string(p, c));
	}
	p = malloc(sizeof(str) * (strlen(str) + 2));
	while (i < strlen(str))
	{
		p[i] = str[i];
		i++;
	}
	p[i] = c;
	p[++i] = '\0';
	return (p);
}

t_type	*parser(char	*line, int dblq, int single)
{
	t_type	*tmp;
	int i;

	tmp = NULL;
	i = 0;
	while (1)
	{
		if (line[i] == '\'' && single == 0 && dblq == 0 )
			single = add_sq(line, &i, '\'', &tmp);
		else if (line[i] == '\''  && single == 1 && dblq == 0)
			single = 0;
		else if (line[i] == '"' && single == 0 && dblq == 0)
			dblq = add_sq(line, &i, '"', &tmp);
		else if (line[i] == '"' && single == 0 && dblq == 1)
			dblq = 0;
		else
			 adds(line, &i, 'o', &tmp);
		if (i >= ft_strlen(line) - 1)
			break;
		i++;
	}
	return (tmp);
}

void	print_types(t_type *type)
{
	t_type *tmp;
	tmp = type;
	while (tmp)
	{
		printf("|word is %s| && |type is %d| \n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_type *tmp;
	g_data = malloc(sizeof(t_data));
	init_env_list(env);
	// printlist(g_data->env);
	while (1)
	{
		if (!(line = readline("ader$>")))
	    	return (1);
		tmp = parser(line, 0, 0);
		add_history(line);
		print_types(tmp);
		check_words(tmp);
		expander(tmp);
	}
	return (0);
}