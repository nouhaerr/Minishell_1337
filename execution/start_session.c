/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/25 14:36:37 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_parser *parser)
{
	while (parser != NULL)
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
		parser = parser->next;
	}
}
