/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:02 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/14 08:18:10 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd(t_parser *parser, int fd[2], char *msg)
{
	pid_t	pid;
	// char	*path;
	// char	*cmd2;

	pid = fork();
	// cmd2 = ft_strdup(parser->cmd);
	// ft_tolower2(cmd2);
	// path = cmd2;
	// if (!cmd_slash(cmd2))
	// 	path = get_path(cmd2);
	// if (!path)
	// 	ft_err("minishell: command not found: ", cmd2);
	// ft_execve(path, cmd2, glb_var.list);
	// free(cmd2);
	if (pid == 0)
	{
		if (!isbuiltin(parser))
		{
			duplicate_fl(parser, fd, msg);
			exec_builtin(parser);
		}
		close(fd[0]);
		duplicate_fl(parser, fd, msg);
		execve(*parser->cmd, parser->cmd, glb_var.list);
	}
}
