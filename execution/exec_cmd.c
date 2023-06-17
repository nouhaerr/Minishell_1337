/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:02 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/17 15:21:41 by nerrakeb         ###   ########.fr       */
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

void	dup_and_exec(t_parser *parse, int *pip, char *msg)
{
	int		*fd;

	fd = fd_redirection(parse);
	if (!fd)
		return ;
	// parse->infiles->fd = fd[0];
	parse->outfiles->fd = pip[1];
	if (!ft_strcmp(msg, "one") || !ft_strcmp(msg, "last"))
	{
		parse->outfiles = 1;
		if (fd[0] == -1)
			parse->infiles->fd = 0;
		if (fd[1] == -1)
			parse->outfiles->fd = 1;
	}
	
}

int	exec_cmd(t_parser *parser, int fd[2], char *msg)
{
	pid_t	pid;
	char	*path;
	char	*cmd2;

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
		dup_and_exec(parser, fd, msg);
		cmd2 = ft_strdup(parse->cmd);
		ft_tolower(cmd2);
		path = cmd2;
		if (!cmd_slash(cmd2))
			path = get_path(cmd2);
		if (!path)
			ft_err("minishell: command not found: ", parse->cmd);
		close(fd[1]);
		if (execve(path, &cmd2, g_var.list) < 0)
		{
			free(cmd2);
			perror("execve");
			exit(1);
		}
		free(cmd2);
	}
	// execve(*parser->cmd, parser->cmd, g_var.list);
	return (pid);
}
