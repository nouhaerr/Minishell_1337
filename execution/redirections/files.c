/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:50:10 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/09 22:08:31 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_open(t_parser *node)
{
    int	fd;

	if (node->outfiles)
	{
		if (node->outfiles->type == finish_up)
			fd = open(node->outfiles->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (node->outfiles->type == clear)
			fd = open(node->outfiles->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (node->infiles)
		fd = open(node->infiles->value, O_RDONLY, 0644);
}
