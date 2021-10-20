/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:13:55 by mamali            #+#    #+#             */
/*   Updated: 2021/10/20 00:42:37 by macbookpro       ###   ########.fr       */
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
		printf("------------------------------------\n");
		t_list	*tmp3 = tmp2->args_list;
		printf("args are : ");
		while (tmp3)
		{
			printf("%s| " , (char *)tmp3->content);
			tmp3 = tmp3->next;
		}
		printf("\n------------------------------------\n");
		printf("in is : %d\n", tmp2->in);
		printf("out is : %d\n", tmp2->out);
		printf("*****************************\n");
		tmp = tmp->next;
	}
}

void	excute_cmd(void)
{
	t_list *tmp;
	t_cmd *tmp2;

	tmp = g_data->cmd_list;
	while (tmp)
	{
		tmp2 = tmp->content;

		if (!strcmp(tmp2->cmd, "echo"))
			builtin_echo(ll_to_dp(tmp2->args_list), NULL);
		tmp = tmp->next;
	}
}
