#include "minishell.h"

void	get_args(t_list **args ,t_type	*types)
{
	t_type	*tmp;
	t_type	*prev;
	
	tmp = types;
	


	while (tmp)
	{
		prev = tmp->prev;


		if (tmp->type != 4)
		{
			if (tmp->prev != NULL)
			{
				if (tmp->prev->type != 4)
					ft_lstadd_back(args, ft_lstnew(tmp->word));
			}
			else
				ft_lstadd_back(args, ft_lstnew(tmp->word));
		}
		tmp = tmp->next;
	}
}

void	expand_cmdlist(void)
{
	t_list *tmp; // copy of t_list tokkens
	t_cmd *cmd;
	t_type *expanded_types;
	t_list	*tmp2;

	tmp = g_data->tokkens;
	while (tmp)
	{
		expanded_types = expander(tmp->content);
		print_types(expanded_types);
		cmd = malloc(sizeof(t_cmd));
		cmd->cmd = expanded_types->word;
		cmd->args_list = NULL;
		get_args(&(cmd->args_list), expanded_types);
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
			/* i add the current list of type t_type to the first node of t_list tokkens
			 so the content of it is a list of type t_type,
			i renew the list of t_type to do the same work 
			after  pipe for the next node of t_list tokkens*/
			ft_lstadd_back(&g_data->tokkens, ft_lstnew(tmp));
			tmp = NULL;
		}
		else if (line[i] == '>' && single == 0 && dblq == 0)
			ft_lstadd_back_type(&tmp,ft_lstnew_type(">", 4));
		else
			adds(line, &i, &tmp);
		// i break the loup when i reach the last charachter of the line
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

char	**ll_to_dp(t_list *list)
{
	int		len;
	int		i;
	char	**str;

	len =  ft_lstsize(list);
	str = malloc(sizeof(char *)  * (len + 1));
	i = 0;
	while (list)
	{
		str[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	str[i] = 0;
	return (str);
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
		excute_cmd();
		//  print_tokkens();
		add_history(line);
		// check_words(tmp);
	}
	return (0);
}

// convert linked list to char **

