/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/30 19:26:52 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_parser *parser)
{
	char	*str;
	t_data	*my_heredoc; // this contains all input of heredoc 	

	my_heredoc = NULL;
	while (parser != NULL)
	{
		if (parser -> cmd != NULL)
		{
		if (!ft_strcmp(parser->cmd, "pwd"))
			sh_pwd();
		else if (!ft_strcmp(parser->cmd, "echo"))
			sh_echo(&parser);
		else if (!ft_strcmp(parser->cmd, "exit"))
			sh_exit(parser);
		else if (!ft_strcmp(parser->cmd, "env"))
			sh_env();
		else if (!ft_strcmp(parser->cmd, "unset"))
			sh_unset(parser->args);
		else if (!ft_strcmp(parser->cmd, "cd"))
			sh_cd(parser);
		}
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