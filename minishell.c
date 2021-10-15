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
		else if (line[i] == '|' && single == 0 && dblq == 0)
		{
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

void	print_tokkens(void)
{
	t_list *tmp;
	t_type *tmp2;

	tmp = g_data->tokkens;
	while (tmp)
	{
		tmp2 = tmp->content;
		print_types(tmp2);
		printf("*****************************\n");
		tmp = tmp->next;
	}
}

void	print_cmd(void)
{
	t_list *tmp;
	t_cmd *tmp2;

	tmp = g_data->cmd_list;
	while (tmp)
	{
		tmp2 = tmp->content;
		printf("cmd is : %s\n", tmp2->cmd);
		printf("args is : []\n");
		printf("in is : %d\n", tmp2->in);
		printf("out is : %d\n", tmp2->out);
		printf("*****************************\n");
		tmp = tmp->next;
	}
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
		print_cmd();
		//  print_tokkens();
		
		add_history(line);
		// check_words(tmp);
	}
	return (0);
}

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
	}
}
