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
	printf("%d\n", cnt);
	if (cnt % 2 == 1)
	{
		cnt = (cnt - 1) / 2;
		while (cnt--)
			ft_lstadd_back(head, ft_lstnew(tmp));
		return (0);
	}
	cnt = cnt / 2;
	printf("%d\n", cnt);
	while (cnt--)
		ft_lstadd_back(head, ft_lstnew(tmp));
	return (1);
}

char    *expand_word(char *str, int type)
{
    char    *p;
    int     i;
    int     cnt;
    t_list  *head;
	t_cl	*tmp;

    
    i = 0;
	head = NULL;
    while (str[i])
    {
		tmp = malloc(sizeof(t_cl));
		tmp->c = str[i];
        cnt = 0;
        if (str[i] ==  '$')
        {
            cnt = real_character1(str, i, '$');
			if (add_bs(&head, cnt))
			{
				
			}
			
        }
        else if (str[i] != '\\')
            ft_lstadd_back(&head, ft_lstnew(tmp));
        i++;
    }
	// printlist_cl(head);
	p = ll_to_string(head);
	//to do
    return (p);
}

char    *expander(t_type *tmp)
{
    t_type  *tmp2;
    int     i;
    char    *s;

    tmp2 = tmp;

    
    while (tmp2)
    {
        i = 0;
        if (tmp2->type == 2 || tmp2->type == 0)
        {
           s = expand_word(tmp2->word, tmp2->type);
            printf("%s\n", s);
        }
        tmp2 = tmp2->next;
    }
    tmp2 = tmp;
    // while (tmp2)
    // {
    //     if (tmp2->type == 2 || tmp2->type == 0)
    //     {

    //     }
    // }
    return (NULL);
}

