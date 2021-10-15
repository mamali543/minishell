#include "minishell.h"

int		add_sq(char *line, int *i, char c, t_type **head)
{
	t_cl	*tmp;
    t_list  *list;
    char *str;
    list = NULL;
    help_q(&list, c);  
    (*i)++;
    // printf("c=%c\n", line[(*i)]);
    while (line[(*i)] != c && line[(*i)])
    {
		tmp = malloc(sizeof(t_cl));
		tmp->c = line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
        (*i)++;
    }
    (*i)--;
    help_q(&list, c);  
    str = ll_to_string(list);
    // printf("%s\n", str);
    if (c == '\'')
	    ft_lstadd_back_type(head,ft_lstnew_type(str, 1));
    else
        ft_lstadd_back_type(head,ft_lstnew_type(str, 2));
    return (1);
}

int		adds(char *line, int *i, t_type **head)
{
	t_cl	*tmp;
    t_list  *list;
    char    **tab;
    char *str;
    int     l;

    l  = 0;
    list = NULL;
    while ((line[(*i)] != '\'' && line[(*i)] != '"' && line[(*i)] != '|' && line[(*i)] != '>') && line[(*i)])
    {
		tmp = malloc(sizeof(t_cl));
		tmp->c = line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
        (*i)++;
    }
    (*i)--;
    str = ll_to_string(list);
    // ft_lstadd_back_type(head,ft_lstnew_type(str, 0));
    tab = ft_split(str, ' ');
    while (tab[l])
    {
	    ft_lstadd_back_type(head,ft_lstnew_type(tab[l], 0));      
        l++;
    }
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