/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:02 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/16 18:04:05 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check(int p)
{
	if (p == -1)
	{
		perror(0);
		exit(EXIT_FAILURE);
	}
}

int	cmd_slash(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_err(char *s, char *cmd)
{
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	exit(127);
}

void	duplicate_fl(t_parser *parse, int *fd, char *msg)
{
	char	*path;
	char	*cmd2;

	fd = fd_redirection(parse);
	cmd2 = ft_strdup(parse->cmd);
	ft_tolower(cmd2);
	path = cmd2;
	if (!cmd_slash(cmd2))
		path = get_path(cmd2);
	if (!path)
		ft_err("pipex: command not found: ", parse->cmd);
	// if (!ft_strcmp(msg, "one"))
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// }
	close(fd[1]);
	if (execve(path, &cmd2, g_var.list) < 0)
	{
		free(cmd2);
		perror("execve");
		exit(1);
	}
	free(cmd2);
}

int	exec_cmd(t_parser *parser, int fd[2], char *msg)
{
	pid_t	pid;

	pid = fork();
	ft_check(pid);
	if (pid == 0)
	{
		// if (!isbuiltin(parser))
		// {
		// 	// duplicate_fl(parser, fd, msg);
		// 	exec_builtin(parser);
		// }
		close(fd[0]);
		duplicate_fl(parser, fd, msg);
	}
	// execve(*parser->cmd, parser->cmd, g_var.list);
	return (pid);
}
