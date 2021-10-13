#include "minishell.h"

// static int     is_in(char *line, int i, char c)
// {
//     int     j;
//     int     f;

//     j = i;
//     f = 0;
//     while (j-- >= 0)
//     {
//         if (line[j] == c)
//         {
//             if (real_character(line, j, '$'))
//             {
//                 f++;
//                 break;
//             }
//         }
//     }
//     j = i;
//     while (line[j])
//     {
//         if (line[j] == c)
//         {
//             if (real_character(line, j, '$'))
//             {
//                 f++;
//                 break;
//             }
//         }
//         j++;
//     }
//     if (line[i] == 36 && f == 0)
//         return (1);
//     if (f == 2)
//         return (1);
//     return (0);
// }

// static int     is_expandable(char *line, int i)
// {
//     int     a;
    
//     a = is_in(line, i, '\'');
//     return (a);
// }

// void    check_args(char *s)
// {
    
// }

int    add_bs(t_list **head, int cnt)
{
	t_cl	*tmp;

	tmp = malloc(sizeof(t_cl));
	tmp->c = '\\';
	if (cnt % 2 == 1)
	{
		cnt = (cnt - 1) / 2;
		while (cnt--)
			ft_lstadd_back(head, ft_lstnew(tmp));
		return (0);
	}
	cnt = cnt / 2;
	while (cnt--)
		ft_lstadd_back(head, ft_lstnew(tmp));
	return (1);
}

void		to_skip(char *s, int *a, t_list **head)
{
	t_cl	*tmp;
	t_list	*list_keys;
	int		i;
	char	*key;

	i = 0;
	list_keys = NULL;
	(*a)++;
	while (((s[(*a)] != '$') && (s[(*a)] != '\'') && (s[(*a)] != ' ')) && s[(*a)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = s[*a];
        ft_lstadd_back(&list_keys, ft_lstnew(tmp));
		(*a)++;
	}
	key = ll_to_string(list_keys);
	printf("key is = %s\n", key);
	char *p = return_env_value(key);
	add_string(head, p);
	(*a)--;
}

char    *expand_word(char *str, t_list **head, int a)
{
    char    *p;
    int     i;
    int     cnt;
	t_cl	*tmp;

    i = 0;
    while (1)
    {
		tmp = malloc(sizeof(t_cl));
		tmp->c = str[i];
        cnt = 0;
        if (str[i] ==  '$')
        {
			cnt = real_character1(str, i, '$');
			if (add_bs(head, cnt))
				to_skip(str , &i, head);
		}
        else if (str[i] == ' ' && a == 0)
		{
			ft_lstadd_back(head, ft_lstnew(tmp));
			while (str[i] == ' ')
				i++;
			i--;
		}
		else
			ft_lstadd_back(head, ft_lstnew(tmp));
		if (i >= ft_strlen(str) - 1)
			break;
		i++;
    }
	// printlist_cl(*head);
	p = ll_to_string(*head);
	//to do
    return (p);
}

t_list	*expander(t_type *tmp)
{
    t_type  *tmp2;
	t_list	*head;
	t_list	*list;
	t_cmd	*cmd;

    tmp2 = tmp;
	head = NULL;
	list = NULL;
	cmd = NULL;
    while (tmp2)
    {
        if (tmp2->type == 2 || tmp2->type == 0)
           expand_word(tmp2->word, &head, tmp2->type);
        else if (tmp2->type == 3)
		{
			cmd = malloc(sizeof(t_cmd));
			cmd->line = ll_to_string(head);
			ft_lstadd_back(&list, ft_lstnew(cmd));
			head = NULL;
		}
		else
			add_string(&head, tmp2->word);
        tmp2 = tmp2->next;
    }
	if (head)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->line = ll_to_string(head);
		ft_lstadd_back(&list, ft_lstnew(cmd));
		head = NULL;
	}
	// printf("line is : %s\n", ll_to_string(head));
    return (list);
}

char	*return_env_value(char *key)
{
	t_list	*env;
	t_env	*tmp;
	int		i;

	env = g_data->env;
	// printlist(g_data->env);
	i = 0;
	while (env)
	{
		tmp = (t_env *)env->content;
		i = ft_strlen(tmp->name);
		if (i == ft_strlen(key))
		{
			if (ft_strcmp(tmp->name, key) == 0)
				return (tmp->content);
		}
		env = env->next;
	}
	return (strdup(""));
}

void	add_string(t_list **head, char *str)
{
	t_cl	*tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = str[i];
		// printf("%c\n", tmp->c);
		ft_lstadd_back(head, ft_lstnew(tmp));
		i++;
	}
	// printlist_cl(*head);
}