#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_libft/libft.h"
# define FALSE 0
# define TRUE 1
# define READ 0
# define WRITE 1
# define SUCCESS 0
# define FAILURE 1
# define KEY_UP 183
# define KEY_DOWN 184
# define ENTER 10
# define KEY_REMOVE 127

typedef struct s_env
{
	char			*name;
	char			*content;
}               t_env;

typedef	struct s_type
{
	char	*word;
	int		type;
	struct s_type *next;

}				t_type;

typedef struct s_counter
{
	int		i;
	int		j;
	int		k;
	int		a;
}				t_counter;


t_list	*init_env_list(char **evnp);
void	printlist(t_list *env);
char    *expander(char *line);
int     real_character(char *line, int i, char c);
t_type	*ft_lstnew_type(char *content, int i);
void	ft_lstadd_back_type(t_type **alst, t_type *new);

#endif