/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:50:10 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/09 22:53:44 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_open(t_parser *node)
{
    int			fd;
	t_parser	*cur;

	cur = node;
	while(cur)
	{
		if (cur->outfiles)
		{
			if (cur->outfiles->type == finish_up)
				fd = open(cur->outfiles->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else if (cur->outfiles->type == clear)
				fd = open(cur->outfiles->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (cur->infiles)
			fd = open(cur->infiles->value, O_RDONLY, 0644);
		cur = cur->next
	}
}
