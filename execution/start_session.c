/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:36:48 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/30 23:27:12 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_parser *parser)
{
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
		parser = parser->next;
	}
}
