#include "minishell.h"

char *ll_to_string(t_list *head)
{
    char    *str;
    // t_cl    *tmp;
    int     len;

    int i;
    
    i = 0;
    len = ft_lstsize(head);
    str = malloc(len + 1);
	// printlist_cl(head);

    while (head)
    {
        printf("-> %c\n", ((t_cl *)head->content)->c);
        str[i] = ((t_cl *)head->content)->c;
        i++;
        head = head->next;
    }
    str[len] = '\0';
    return (str);
}