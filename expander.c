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

char    *expander(t_type *tmp)
{
    t_type  *tmp2;
    int     i;

    tmp2 = tmp;
    while (tmp2)
    {
        i = 0;
        if (tmp2->type == 2 || tmp2->type == 0)
        {
            while (tmp2->word[i])
            {
                if (real_character(tmp2->word, i, '$'))
                {
                    // check_args(tmp2->word + i + 1);
                    tmp2->exp = 1;
                    break ;
                }
                i++;
            }
        }
        tmp2 = tmp2->next;
    }
    tmp2 = tmp;
    while (tmp2)
    {
        if (tmp2->type == 2 || tmp2->type == 0)
        {

        }
    }
    return (NULL);
}