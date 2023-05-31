/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/30 19:43:43 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir(t_parser *parser)
{
	char	*str;
	t_data	*my_heredoc; // this contains all input of heredoc 	

	my_heredoc = NULL;
	while (parser != NULL)
	{
		if (parser -> heredoc != NULL)
		{
			str = her(parser -> heredoc, glb_var.list);
			ft_lstaddback2(&my_heredoc, ft_lstnew2(str));
		}
		parser = parser->next;
	}	
}

// this is just to check if my linked lst my_heredoc contains what it must contain.
// while (my_heredoc)
// 	{
// 		printf("%s\n", my_heredoc -> value);
// 		my_heredoc = my_heredoc -> next;
// 	}