/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:29:16 by macbookpro        #+#    #+#             */
/*   Updated: 2021/10/22 13:40:53 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    create_file(char *s, t_cmd *cmd)
{
    int fd;

 	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC , 0777);
    cmd->out = fd; 
}

