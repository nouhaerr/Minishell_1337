/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/26 15:49:07 by hobenaba         ###   ########.fr       */
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
			if (!ft_strcmp(parser->cmd->value, "pwd"))
				sh_pwd();
			else if (!ft_strcmp(parser->cmd->value, "echo"))
				sh_echo(&parser);
			else if (!ft_strcmp(parser->cmd->value, "exit"))
				sh_exit(parser);
			else if (!ft_strcmp(parser->cmd->value, "env"))
				sh_env();
			else if (!ft_strcmp(parser->cmd->value, "unset"))
				sh_unset(parser->args);
		}
		if (parser -> heredoc != NULL)
		{
			str = her(parser -> heredoc, glb_var.list);
			ft_lstaddback2(&my_heredoc, ft_lstnew2(str));
		}
		parser = parser->next;
	}
}
