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

// kanhez env variable f list o kancovrtiha l string
void		to_skip(char *s, int *a, t_list **head, int f)
{
	t_cl	*tmp;
	t_list	*list_keys;
	int		i;
	char	*key;
	char	*p;

	i = *a;
	list_keys = NULL;
	if (s[i + 1] == '\'')
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = s[*a];
        ft_lstadd_back(&list_keys, ft_lstnew(tmp));
		key = ll_to_string(list_keys);
		add_string(head, key);
		return ;
	}
	(*a)++;
	while (((s[(*a)] != '$') && (s[(*a)] != '\'') && (s[(*a)] != ' ') \
		&& (s[(*a)] != '"') && (s[(*a)] != '-')) && s[(*a)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = s[*a];
        ft_lstadd_back(&list_keys, ft_lstnew(tmp));
		(*a)++;
	}
	key = ll_to_string(list_keys);
	printf("kay = %s\n", key);
	key = return_env_value(key);
	add_string(head, key);
	(*a)--;
}
// ila kan khasso yt2expanda kanb6a n2ajouter f les charactres f wahd list
// hta kanl6a $ HHHHH
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
			//ila l6it $ kanskipi kolchi hta kanl6a 
			// '', "", ' ', $
			cnt = real_character1(str, i, '$');
			if (add_bs(head, cnt))
			{
				to_skip(str , &i, head, a);
			}
		}
        else if (str[i] == ' ' && a == 0)
		{
			//ila kan type d lword 0 o l6It espace kanzid espace lewla
			// o kanskipi les espaces lakhrine
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

t_type	*ft_lstnew_type2(char *content, int i)
{
	t_type *new;

	new = (t_type *)malloc(sizeof(t_type) * 1);
    new->word = content;
    new->type = i;
	new->next = NULL;
	return (new);
}

//loup eela list type kandistingui fiha type dyal l words li eendi f list
// o kanreturni had list me2expandia
t_type	*expander(t_type *tmp)
{
    t_type  *tmp2;
    t_type  *new;
	t_list	*head;
	char	*str;


    tmp2 = tmp;
	new = NULL;
    while (tmp2)
    {
		head = NULL;
        if (tmp2->type == 2 || tmp2->type == 0)
		{
			// printf("%s\n", tmp2->word);
           expand_word(tmp2->word, &head, tmp2->type);
		}
		else
			add_string(&head, tmp2->word);
		str = ll_to_string(head);
		if (tmp2->type == 0)
			add_tab_to_ll(&new, str, tmp2->type);
		else
 			ft_lstadd_back_type(&new, ft_lstnew_type2(str, tmp2->type));
        tmp2 = tmp2->next;
    }
    return (new);
}

void	add_tab_to_ll(t_type **head, char *str, int type)
{
	char **tab;
	int	i;

	i = 0;
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		ft_lstadd_back_type(head, ft_lstnew_type2(tab[i], type));
		i++;
	}
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
		// printf("new key = %c\n", key[i - 1]);
		tmp = (t_env *)env->content;
		i = ft_strlen(tmp->name);
		if (i == ft_strlen(key))
		{
			if (ft_strcmp(tmp->name, key) == 0)
				return (tmp->content);
		}
		env = env->next;
	}
	return (ft_strdup(""));
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

void	free_nodes_types(t_type	**tmp)
{
	t_type	*tmp2;
	tmp2 = *tmp;
	while (*tmp)
	{
		tmp2 = *tmp;
		if (tmp2->word != NULL)
			free(tmp2->word);
		free(tmp2);
		*tmp = (*tmp)->next;
	}
}