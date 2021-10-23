#include "minishell.h"

void	add_in(char *line, size_t *i, char c, t_type **head)
{
	t_cl	*tmp;
	t_list  *list;
	char	*str;
	size_t	k;

	list = NULL;
	printf("hey\n");
	while (line[(*i)] == c && line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	(*i)--;
	str = ll_to_string(list);
	k = ft_strlen(str);
	if (k == 1)
		ft_lstadd_back_type(head,ft_lstnew_type(str, 6, 0));
	else if (k == 2)
		ft_lstadd_back_type(head,ft_lstnew_type(str, 5, 0));
	else
	{
		printf("error\n");
		exit(1);
	}
}
void	add_out(char *line, size_t *i, char c, t_type **head)
{
	t_cl	*tmp;
	t_list  *list;
	char	*str;
	size_t	k;

	list = NULL;
	while (line[(*i)] == c && line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	(*i)--;
	str = ll_to_string(list);
	k = ft_strlen(str);
	if (k == 1)
		ft_lstadd_back_type(head,ft_lstnew_type(str, 4, 0));
	else if (k == 2)
		ft_lstadd_back_type(head,ft_lstnew_type(str, 3, 0));
	else
	{
		printf("error\n");
		exit(1);
	}
}

/*since i didn't meet the c charachter i add the charchters between '' or "" in a struct type t_cl that add a charchter in a c variable
 and i add all the structs back to each others in a list of type t_list
 then i convert the list to a string, finally i add the string to a list of type t_type that
 contains the string and his type. */

int		add_sq(char *line, size_t *i, char c, t_type **head)
{
	t_cl	*tmp;
	t_list  *list;
	char *str;
	list = NULL;
	// help_q(&list, c); 
	(*i)++;
	while (line[(*i)] != c && line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	// help_q(&list, c);
	str = ll_to_string(list);
    if (c == '\'')
	{
		(*i)++;
		if (line[(*i)] == ' ')
			ft_lstadd_back_type(head,ft_lstnew_type(str, 1, 0));
		else
			ft_lstadd_back_type(head,ft_lstnew_type(str, 1, 1));
	}
	else
	{
		(*i)++;
		if (line[(*i)] == ' ' || !line[(*i)])
			ft_lstadd_back_type(head,ft_lstnew_type(str, 2, 0));
		else
			ft_lstadd_back_type(head,ft_lstnew_type(str, 2, 1));
	}
	(*i)--;
	(*i)--;
	return (1);
}

/*i add the charchters till i meet '', "", |, or >  in a struct type t_cl that add a charchter in a c variable
 and i add all the structs back to each others in a list of type t_list
 then i convert the list to a string, finally i add the string to a list of type t_type that
 contains the string and his type.*/

int		adds(char *line, size_t *i, t_type **head)
{
	t_cl	*tmp;
	t_list  *list;
	char    **tab;
	char *str;
	int     l;
	int		f;

	l  = 0;
	f = 0;
	list = NULL;
	while ((line[(*i)] != '\'' && line[(*i)] != '"' && line[(*i)] != '|' && line[(*i)] != '>' && line[(*i)] != '<') && line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	str = ll_to_string(list);
	// ft_lstadd_back_type(head,ft_lstnew_type(str, 0));
	tab = ft_split(str, ' ');
	while (tab[l])
		l++;
	printf("%d\n", l);
	printf("c = %c\n", line[(*i)]);
	if (l == 1)
		ft_lstadd_back_type(head,ft_lstnew_type(tab[0], 0, 0));
	else
	{
		while (tab[f] && f < (l - 1))
		{
			printf("hey\n");
			ft_lstadd_back_type(head,ft_lstnew_type(tab[f], 0, 0));      
			f++;
		}
		if (line[(*i)] == '\'' || line[(*i)] == '"')
		{
			printf("heyy\n");
			ft_lstadd_back_type(head,ft_lstnew_type(tab[f], 0, 1));
		}
		else
			ft_lstadd_back_type(head,ft_lstnew_type(tab[f], 0, 0));
	}
	// l = 0;
	// while (tab[l])
	// {
	// 	printf("tab[%d] = %s\n", l, tab[l]);
	// 	l++;
	// }
	(*i)--;
	return (1);
}

// int    check_if_sq(char *str, int *j)
// {
//     int     i;

//     i = 0;
//     while (str[i] != '$')
//     {
//         if (str[i] == '\'')
//         {
//             while (str[i] != '$')
//                 (*j)++;
//         }
//         i++;
//     }
//     return (*j);
// }

void    help_q(t_list **head, char c)
{
	t_cl	*tmp;

	tmp = malloc(sizeof(t_cl));
	tmp->c = c;
	ft_lstadd_back(head, ft_lstnew(tmp));
}

char	*my_ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	p = malloc(i + j + 2);
	if (!(p))
		return (0);
	ft_strcpy(p, (char *)s1);
	ft_strcpy(&p[i], "/");
	ft_strcpy(&p[i + 1], (char *)s2);
	return (p);
}

char	*get_absolute_path(char **path, char *str)
{
	int		i;
	int		fd;
	char	*cmd;

	i = -1;
	cmd = NULL;
	while (path[++i])
	{
		cmd = my_ft_strjoin(path[i], str);
		// printf("cmd=%s\n", cmd);
		fd = open(cmd, O_RDONLY);
		if (fd > 0)
			break ;
		close(fd);
	}
	close(fd);
	return (cmd);
}

void	free_dpointer(char	**tokkens)
{
	int		i;

	i = 0;
	while (tokkens[i])
	{
		free(tokkens[i]);
		i++;
	}
	free(tokkens);
}

char	*get_cmd_path(char *str, t_list *env)
{
	t_list	*env_tmp;
	char	**path;
	char	*cmd;
	t_env	*env_l;
	int		i;

	env_tmp = env;
	i = 0;
	while (env_tmp)
	{
		env_l = env_tmp->content;
		if (!(ft_strncmp(env_l->name, "PATH", 4)))
			cmd = env_l->content;
		env_tmp = env_tmp->next;
	}
	path = ft_split(cmd, ':');
	str = get_absolute_path(path, str);
	free_dpointer(path);
	return (str);
}