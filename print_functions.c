/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:13:55 by mamali            #+#    #+#             */
/*   Updated: 2021/10/15 16:14:12 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_types(t_type *type)
{
	t_type *tmp;
	tmp = type;
	while (tmp)
	{
		printf("|word is %s| && |type is %d| \n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}

void	print_tokkens(void)
{
	t_list *tmp;
	t_type *tmp2;

	tmp = g_data->tokkens;
	while (tmp)
	{
		tmp2 = tmp->content;
		print_types(tmp2);
		printf("*****************************\n");
		tmp = tmp->next;
	}
}

void	print_cmd(void)
{
	t_list *tmp;
	t_cmd *tmp2;

	tmp = g_data->cmd_list;
	while (tmp)
	{
		tmp2 = tmp->content;
		printf("cmd is : %s\n", tmp2->cmd);
		printf("args is : []\n");
		printf("in is : %d\n", tmp2->in);
		printf("out is : %d\n", tmp2->out);
		printf("*****************************\n");
		tmp = tmp->next;
	}
}
