#include "minishell.h"

/*since i didn't meet the c charachter i add the charchters between '' or "" in a struct type t_cl that add a charchter in a c variable
 and i add all the structs back to each others in a list of type t_list
 then i convert the list to a string, finally i add the string to a list of type t_type that
 contains the string and his type. */

int		add_sq(char *line, int *i, char c, t_type **head)
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
    (*i)--;
    // help_q(&list, c);
    str = ll_to_string(list);
    if (c == '\'')
	    ft_lstadd_back_type(head,ft_lstnew_type(str, 1));
    else
        ft_lstadd_back_type(head,ft_lstnew_type(str, 2));
    return (1);
}

/*i add the charchters till i meet '', "", |, or >  in a struct type t_cl that add a charchter in a c variable
 and i add all the structs back to each others in a list of type t_list
 then i convert the list to a string, finally i add the string to a list of type t_type that
 contains the string and his type.*/

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