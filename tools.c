#include "minishell.h"

t_type	*ft_lstnew_type(char *content, int i)
{
	t_type *new;

	new = (t_type *)malloc(sizeof(t_type) * 1);
	new->word = strdup(content);
    new->type = i;
	new->next = NULL;
	return (new);
}

t_type	*ft_lstlasttype(t_type *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_type(t_type **alst, t_type *new)
{
	new->next = NULL;
	if (!(*alst))
		*alst = new;
	else
		ft_lstlasttype(*alst)->next = new;
}


int     real_character(char *line, int i, char c)
{
    int cnt;
    int ret;

    cnt = 0;
    ret = 0;

    if (line[i] == c)
    {
        if (i == 0)
            return (1);
        i--;
        if (line[i] ==  '\\')
        {
            while (line[i--] ==  '\\')
                cnt++;
            if (cnt % 2 == 0)
                return (1);
        }
        else
            return (1);
    }
    return (0);
}
