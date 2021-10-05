#include "minishell.h"

int		add_sq(char *line, int *i, char c, t_type **head)
{
	t_cl	*tmp;
    t_list  *list;
    char *str;
    list = NULL;
    (*i)++;
    while (line[(*i)] != c && line[(*i)])
    {
		tmp = malloc(sizeof(t_cl));
		tmp->c = line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
        (*i)++;
    }
    str = ll_to_string(list);
	ft_lstadd_back_type(head,ft_lstnew_type(str, 1));
    return (1);
}

int		adds(char *line, int *i, char c, t_type **head)
{
	t_cl	*tmp;
    t_list  *list;
    char *str;
    list = NULL;
    while (line[(*i)] != '\''  && line[(*i)])
    {
        printf("cac = %c\n", line[(*i)]);
		tmp = malloc(sizeof(t_cl));
		tmp->c = line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
        (*i)++;
    }
    (*i)--;

    str = ll_to_string(list);
	ft_lstadd_back_type(head,ft_lstnew_type(str, 0));
    return (1);
}