#include "minishell.h"

static int     is_in(char *line, int i, char c)
{
    int     j;
    int     f;

    j = i;
    f = 0;
    while (j-- >= 0)
    {
        if (line[j] == c)
        {
            if (real_character(line, j, '$'))
            {
                f++;
                break;
            }
        }
    }
    j = i;
    while (line[j])
    {
        if (line[j] == c)
        {
            if (real_character(line, j, '$'))
            {
                f++;
                break;
            }
        }
        j++;
    }
    if (line[i] == 36 && f == 0)
        return (1);
    if (f == 2)
        return (1);
    return (0);
}

static int     is_expandable(char *line, int i)
{
    int     a;
    
    a = is_in(line, i, '\'');
    return (a);
}

char    *expander(char *line)
{
    char    *str;
    int     i;

    i = 0;
    while (line[i])
    {
        if (i != 0)
        {
            if (real_character(line, i, '$'))
            {
                if (is_expandable(line, i) == 1)
                {

                    printf("work\n");
                }
            }
        }
        i++;
    }
    return (NULL);
}