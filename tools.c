#include "minishell.h"

int     real_character(char *line, int i)
{
    int cnt;
    int ret;

    cnt = 0;
    ret = 0;
    i--;

    if (line[i] == '\\')
    {
        while (line[i--] == '\\')
            cnt++;
        if (cnt % 2 == 0)
            ret = 1;
    }
    else
        ret = 1;
    return (ret);
}