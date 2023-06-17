/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bltn_hered.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/17 19:06:24 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_heredoc(t_parser *parser, t_data **my_heredoc)
{
	char	*str;

	while (parser)
	{
		if (parser -> heredoc != NULL)
		{
			str = her(parser -> heredoc, g_var.list);
			ft_lstaddback2(my_heredoc, ft_lstnew2(str));
			free (str);
		}
		parser = parser -> next;
	}
}

void	exec_builtin(t_parser *parser)
{
	char	*cmd2;

	cmd2 = ft_strdup(parser->cmd);
	ft_tolower2(cmd2);
	if (!ft_strcmp(cmd2, "pwd"))
		sh_pwd();
	else if (!ft_strcmp(cmd2, "echo"))
		sh_echo(&parser);
	else if (!ft_strcmp(parser->cmd, "exit"))
		sh_exit(parser);
	else if (!ft_strcmp(cmd2, "env"))
		sh_env();
	else if (!ft_strcmp(parser->cmd, "unset"))
		sh_unset(parser->args);
	else if (!ft_strcmp(cmd2, "cd"))
		sh_cd(parser);
	else if (!ft_strcmp(parser->cmd, "export"))
		sh_export(parser);
	free(cmd2);
}
