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

t_type	*parser(char	*line)
{
	t_type	*tmp;
	int		single;
	int		dblq;
	char	*str;

	single = 0;
	dblq = 0;
	tmp = NULL;
	str = ft_strdup("");
	int i;
	i = 0;
	while (line[i])
	{
		if (real_character(line, i, '\'')  && single == 0 && dblq == 0 )
		{

		    if (ft_strcmp("", str) != 0)
				ft_lstadd_back_type(&tmp,ft_lstnew_type(str, 0));
			single = 1;
			free(str);
			str = ft_strdup("");
		}
		else if (real_character(line, i, '\'') && single == 1 && dblq == 0)
		{
			str = make_string(str, line[i]);
			ft_lstadd_back_type(&tmp,ft_lstnew_type(str, 1));
			if (line[i + 1])
				i++;
			else
			{	
				single = 0;
				free(str);
				str = ft_strdup("");
				break;
			}
			free(str);
			single = 0;
			str = ft_strdup("");
		}
		else if (real_character(line, i, '"') && single == 0 && dblq == 0)
		{
			if (strcmp("", str) != 0)
				ft_lstadd_back_type(&tmp,ft_lstnew_type(str, 0));
			dblq = 1;
			free(str);
			str = ft_strdup("");
		}
		else if (real_character(line, i, '"') && single == 0 && dblq == 1)
		{
			str = make_string(str, line[i]);
			ft_lstadd_back_type(&tmp,ft_lstnew_type(str, 2));
			if (line[i + 1])
				i++;
			else
			{	
				dblq = 0;
				free(str);
				str = ft_strdup("");
				break;
			}
			free(str);
			dblq = 0;
			str = ft_strdup("");
		}
		str = make_string(str, line[i]);
		i++;
	}
	if (str)
		ft_lstadd_back_type(&tmp,ft_lstnew_type(str, 0));
	return (tmp);
}

void	print_types(t_type *type)
{
	t_type *tmp;
	tmp = type;
	while (tmp)
	{
		printf("|word is %s| && |type is %d| \n | exp : %d\n", tmp->word, tmp->type, tmp->exp);
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
		tmp = parser(line);
		check_words(tmp);
		expander(tmp);
		print_types(tmp);

	}
	return (0);
}