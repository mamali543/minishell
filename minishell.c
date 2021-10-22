#include "minishell.h"

t_list	*get_args(t_list **args ,t_type	*types)
{
	t_type	*tmp;
	t_type	*tmp1;
	t_type	*prev;
	t_list	*list_files;
	
	tmp = types;
	list_files = NULL;
	while (tmp)
	{
		prev = tmp->prev;
		if (tmp->type == 4)
		{
			tmp1 = tmp;
			ft_lstadd_back(&list_files, ft_lstnew(tmp1->next->word));
		}
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
	return (list_files);
}


void	get_out(int *i, t_list *list_files)
{
	char	*s;

	if (list_files)
	{
		s = ft_lstlast(list_files)->content;
		printf("file out = %s\n", s);
		*i = open(s, O_WRONLY | O_CREAT | O_TRUNC , 0777);
		while (ft_strcmp(s, list_files->content) != 0)
		{
			open(list_files->content, O_WRONLY | O_CREAT | O_TRUNC , 0777);
			list_files = list_files->next;
		}
	}
}

int	ft_lstsize_type(t_type *type)
{
	int		i;

	i = 0;
	if (type)
	{
		while (type)
		{
			i++;
			type = type->next;
		}
	}
	return (i);
}

t_type	*ft_lstlast_type(t_type *type)
{
	if (!type)
		return (type);
	while (type->next)
		type = type->next;
	return (type);
}

t_type	*get_cmd(t_type *type)
{
	t_type	*tmp;
	int		i;

	tmp = type;
	i = 0;
	while (tmp->next->word[i] != '-')
		tmp = tmp->next;
	return (tmp);
}

void	expand_cmdlist(void)
{
	t_list *tmp;
	t_cmd *cmd;
	t_type *expanded_types;
	t_list	*list_files;
	int		i;
	t_type	*tmp2;
	char	*str;

	tmp = g_data->tokkens;
	i = 0;
	while (tmp)
	{
		tmp2 = tmp->content;
		expanded_types = expander(tmp->content);
		// print_types(expanded_types);
		cmd = malloc(sizeof(t_cmd));
		if (i == 0)
		{
			printf("type : %d\n", tmp2->type);
			if (tmp2->type == 4)
			{
				print_types(tmp2);
				str = ft_lstlast_type(tmp2)->word;
				if (str[i] == '-')
					str = get_cmd(tmp2)->word;
				else
					str = ft_lstlast_type(tmp2)->word;
				cmd->cmd = get_cmd_path(str, g_data->env);
				cmd->args_list = NULL;
				list_files = get_args(&(cmd->args_list), expanded_types);
				get_out(&(cmd->out), list_files);
				cmd->in = 1;
			}
			else if (tmp2->type == 0)
			{
				cmd->cmd = get_cmd_path(expanded_types->word, g_data->env);
				cmd->args_list = NULL;
				list_files = get_args(&(cmd->args_list), expanded_types);
				get_out(&(cmd->out), list_files);
				cmd->in = 1;	
			}
		}
		else
		{
			cmd->cmd = get_cmd_path(expanded_types->word, g_data->env);
			cmd->args_list = NULL;
			list_files = get_args(&(cmd->args_list), expanded_types);
			get_out(&(cmd->out), list_files);
			cmd->in = 1;
		}
		ft_lstadd_back(&g_data->cmd_list, ft_lstnew(cmd));
		tmp = tmp->next;
		i++;
		printf("--------------------\n");
	}
}

char	*make_string(char *str, char c)
{
	size_t		i;
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
	size_t i;

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
		{
			// if (line[i + 1] == '>')
				add_append(line, &i, '>', &tmp);
			// ft_lstadd_back_type(&tmp,ft_lstnew_type(">", 4));
		}
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
	argc = 0;
	argv = NULL;
	while (1)
	{
		g_data->tokkens = NULL;
		g_data->cmd_list = NULL;
		if (!(line = readline("ader$>")))
	    	return (1);
		parser(line, 0, 0);
		// expand_cmdlist();
		// print_cmd();
		// excute_cmd();
		 print_tokkens();
		add_history(line);
		// check_words(tmp);
	}
	return (0);
}


