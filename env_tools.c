#include "minishell.h"

t_list	*init_env_list(char **envp)
{
	int		i;
	char	**s;
	t_env	*a;
    t_list  *env;

	i = 1;
	a = malloc(sizeof(t_env));
	s = ft_split(envp[0], '=');
	a->name = s[0];
	a->content = s[1];
	env = ft_lstnew(a);
	free(s);
	while (envp[i])
	{
		s = ft_split(envp[i], '=');
		a = malloc(sizeof(t_env));
		a->name = s[0];
		a->content = s[1];
		ft_lstadd_back(&(env), ft_lstnew(a));
		free(s);
		i++;
	}
    return(env);
}

void	printlist(t_list *env)
{
	t_list		*lst;
	t_env		*env_l;

	lst = env;
	while (lst)
	{
		env_l = lst->content;
		printf("%s=%s\n", env_l->name, env_l->content);
		lst = lst->next;
	}
}

void	printlist_cl(t_list *env)
{
	t_list		*lst;
	t_cl		*env_l;

	lst = env;
	while (lst)
	{
		env_l = lst->content;
		printf("| %c |\n", env_l->c);
		lst = lst->next;
	}
}
