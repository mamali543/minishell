#include "minishell.h"

void    log_error(char *s, int i)
{
    ft_putstr(s);
    // exit(125);
}

void    check_words(t_type *tmp)
{
    t_type  *tmp2;
    int     i;

    tmp2 = tmp;
    i = 0;
    while (tmp2)
    {
        if (tmp2->word[0] == '\'')
        {
            if (ft_strlen(tmp2->word) == 1)
                log_error("syntax_error\n", 2);
            i = ft_strlen(tmp2->word);
            if (tmp2->word[i - 1] != '\'')
            {
                log_error("syntax_error\n", 2);
            }
        }
        else if (tmp2->word[0] == '"')
        {
            if (ft_strlen(tmp2->word) == 1)
                log_error("syntax_error\n", 2);
            i = ft_strlen(tmp2->word);
            if (tmp2->word[i - 1] != '"')
                log_error("syntax_error\n", 2);
        }
        tmp2 = tmp2->next;
    }
}

t_type	*ft_lstnew_type(char *content, int i)
{
	t_type *new;

	new = (t_type *)malloc(sizeof(t_type) * 1);
	new->word = strdup(content);
    new->type = i;
    new->exp = 0;
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
