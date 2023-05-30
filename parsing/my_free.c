/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:56:47 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/27 17:46:48 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data1(t_data *list)
{
	t_data	*list2;

	while (list)
	{
		list2 = (list)-> next;
		free(list);
		list = list2;
	}
}

void	free_data2(t_data2 *list)
{
	t_data2	*list2;

	while (list)
	{
		list2 = (list)-> next;
		free(list);
		list = list2;
	}
}

void	free_parser(t_parser *list)
{
	t_parser	*list2;

	while (list)
	{
		list2 = list -> next;
		free_data2(list ->outfiles);
		free(list -> cmd);
		free_data1(list -> args);
		free_data1(list -> infiles);
		free_data2(list -> heredoc);
		free(list);
		list = list2;
	}
}

void	free_lexer(t_token *list)
{
	t_token	*list2;

	while (list)
	{
		free(list -> value);
		list2 = list -> next;
		free(list);
		list = list2;
	}
}

void	free_mylist(void *list, int type)
{
	if (type == 0)
		free_lexer((t_token *)list);
	else
	{
		free_parser((t_parser *)list);
	}
}
