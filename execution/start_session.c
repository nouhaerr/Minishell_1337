/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/24 17:48:21 by nerrakeb         ###   ########.fr       */
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
		parser = parser->next;
	}
}
