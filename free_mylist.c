/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mylist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:52:25 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 10:51:47 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_mylist(void *list, int type)
{
	t_token		*t;
	t_parser	*p;
	t_token		*t1;
	t_parser	*p1;

	if (type == 0)
	{
		t = (t_token *)list;
		while (t)
		{
			free(t -> value);
			t1 = t -> next;
			free(t);
			t = t1;
		}
	}
	else
	{
		p = (t_parser *)list;
		while (p)
		{
			p1 = p -> next;
			while(p ->args)
			{
				t_data2 *args2;
				args2 = (p -> args) -> next;
				free(p -> args);
				p -> args = args2;
			}
			while(p ->cmd)
			{
				t_data *cmd2;
				cmd2 = (p -> cmd) -> next;
				free(p -> cmd);
				p -> cmd = cmd2;
			}
			while(p ->outfiles)
			{
				t_data2 *outfiles2;
				outfiles2 = (p -> outfiles) -> next;
				free(p -> outfiles);
				p -> outfiles = outfiles2;
			}
			while(p ->infiles)
			{
				t_data *infiles2;
				infiles2 = (p -> infiles) -> next;
				free(p -> infiles);
				p -> infiles = infiles2;
			}
			while(p ->heredoc)
			{
				t_data *heredoc2;
				heredoc2 = (p -> heredoc) -> next;
				free(p -> heredoc);
				p -> heredoc = heredoc2;
			}
			free(p);
			p = p1;
		}
	}
}
