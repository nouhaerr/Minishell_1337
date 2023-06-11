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

int	ft_open(char *name, char *msg)
{
	int	fd;

	if (!ft_strcmp(msg, "saved_file"))
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (!ft_strcmp(msg, "outfile"))
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(name, O_CREAT | O_RDONLY, 0644);
	if (fd == -1)
	{
		perror(name);
		if (pid != 0) //ila kena fl parent
			exit(1);
		else
			fd = -3;
	}
	return (fd);
}

int	fd_redirection(t_parser *node)
{
    int			*fd;
	t_parser	*cur;
	t_data2		*tmp1;
	t_data		*tmp2;

	fd = malloc(sizeof(int) * 2);
	cur = node;
	tmp1 = node->outfiles;
	tmp2 = node->infiles;
	while(cur)
	{
		while (tmp1)
		{
			if (tmp1->type == finish_up)
				fd[1] = ft_open(tmp1->value, "saved_file");
			else if (tmp1->type == clear)
				fd[1] = ft_open(tmp1->value, "outfile");
			if (fd[1] == -3)
				return (free(fd), NULL);
			tmp1 = tmp1->next;
		}
		while (tmp2)
			fd[0] = ft_open(tmp2->value, "infile");
			tmp2 = tmp2->next;
		cur = cur->next;
	}
	return (fd);
}
