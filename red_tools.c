/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:29:16 by macbookpro        #+#    #+#             */
/*   Updated: 2021/10/15 06:29:35 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    create_file(char *s, int type, t_cmd *cmd)
{
    int fd;

 	fd = open(s, O_WRONLY | O_CREAT | O_TRUNC , 0777);
    cmd->out = fd; 
}

