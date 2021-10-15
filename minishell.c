#include "minishell.h"

void	expand_cmdlist(void)
{
	t_list *tmp;
	t_cmd *cmd;
	t_type *type_copy;

	tmp = g_data->tokkens;
	while (tmp)
	{
		type_copy = expander(tmp->content);
		print_types(type_copy);
		cmd = malloc(sizeof(t_cmd));
		cmd->cmd = type_copy->word;
		cmd->in = 1;
		cmd->out = 0;
		ft_lstadd_back(&g_data->cmd_list, ft_lstnew(cmd));
		tmp = tmp->next;
		printf("--------------------\n");
	}
}

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

//parser: i take the line i fill words depends on their types in a t_type list, whenever i find a pipe i add the t_type list in a t_list tokkens and i free the t_type list.

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
		else if (line[i] == '|' && single == 0 && dblq == 0)
		{
			/* i add the  tmp list to the t_list tokkens and i start fill tmp 
			with the new words after  pipe for the next node of t_list tokkens*/
			ft_lstadd_back(&g_data->tokkens, ft_lstnew(tmp));
			tmp = NULL;
		}
		else if (line[i] == '>' && single == 0 && dblq == 0)
			ft_lstadd_back_type(&tmp,ft_lstnew_type(">", 4));
		else
			adds(line, &i, &tmp);
		if (i >= ft_strlen(line) - 1)
			break;
		i++;
	}
	if (tmp)
	{
		ft_lstadd_back(&g_data->tokkens, ft_lstnew(tmp));
		tmp = NULL;
	}
	return (tmp);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;

	g_data = malloc(sizeof(t_data));
	init_env_list(env);
	while (1)
	{
		g_data->tokkens = NULL;
		g_data->cmd_list = NULL;
		if (!(line = readline("ader$>")))
	    	return (1);
		parser(line, 0, 0);
		expand_cmdlist();
		// print_cmd();
		//  print_tokkens();
		add_history(line);
		// check_words(tmp);
	}
	return (0);
}

char	**function(t_type		*types)
{
	char	
}