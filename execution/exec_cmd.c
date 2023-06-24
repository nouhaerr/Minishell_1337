/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:02 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/24 18:26:31 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_fork(int p)
{
	if (p == -1)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

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

int	*dup_fd(t_parser *parse, t_pipe pip, char *msg)
{
	int		*fl;

	fl = fd_redirection(parse);
		parse->fd[1] = 1;
	if (!fl)
		return (0);
	if (!ft_strcmp(msg, "one"))
	{
		parse->fd[0] = 0;
		if (fl[0] != -1)
			parse->fd[0] = fl[0];
		if (fl[1] != -1)
			parse->fd[1] = fl[1];
	printf("%d\t%d\n", parse->fd[0], parse->fd[1]);
	}
	else
	{
		parse->fd[1] = pip.wr_end[1];
		parse->fd[0] = 0;
		if (!ft_strcmp(msg, "first"))
		{
			if (fl[0] != -1)
				parse->fd[0] = fl[0];
			if (fl[1] != -1)
				parse->fd[1] = fl[1];
		}
		if (!ft_strcmp(msg, "last"))
		{
			parse->fd[1] = 1;
			parse->fd[0] = pip.rd_end[0];
			if (fl[0] != -1)
				parse->fd[0] = fl[0];
			if (fl[1] != -1)
				parse->fd[1] = fl[1];
		}
		if (!ft_strcmp(msg, "between"))
		{
			parse->fd[0] = pip.rd_end[0];
			parse->fd[1] = pip.wr_end[1];
			if (fl[0] != -1)
				parse->fd[0] = fl[0];
			if (fl[1] != -1)
				parse->fd[1] = fl[1];
		}
	}
	// printf(" write:%d read:%d\n", parse->fd[1], parse->fd[0]);
	dup2(parse->fd[1], 1);
	dup2(parse->fd[0], 0);
	if (ft_strcmp(msg, "one"))
	{
		close(pip.rd_end[0]);
		close(pip.rd_end[1]);
		close(pip.wr_end[0]);
		close(pip.wr_end[1]);
	}
	return (fl);
}

void	ft_execve(char *path, t_parser *node, char **env)
{
	char	**arr;
	int	dir;

	dir = open(path, O_DIRECTORY);
	if (dir != -1) //means that it's a directory
	{
		close(dir);
		ft_err("minishell: ", path, ":is a directory");
		g_var.exit_status = 126;
		exit(g_var.exit_status);
	}
	arr = table_cmd(node);
	// if (access(path, X_OK)) //not executable
	//		exit(126);
	//printf("HERE %s\n", *arr); // && access(path, X_OK | F_OK)
	if (execve(path, arr, env) < 0)
	{
		free(env);
		perror("minishell");
		// printf("ok\n");
		// if (cmd_slash(node->cmd))
		// 	ft_err("minishell: ", node->cmd, ": No such file or directory");
		// else if (!cmd_slash(node -> cmd) && node -> my_cmd == 0)
		// 	ft_err("minishell: ", node->cmd, ": command not found");
		exit(g_var.exit_status);
	}
	free(env);
}

void	dp_built(t_parser *parse, t_pipe pip, char *msg)
{
	dup_fd(parse, pip, msg);
	if (isbuiltin(parse))
	{
		run_builtin(parse);
		update_fd(g_var.fd_prog);
		exit(g_var.exit_status);
	}
	if (!parse->cmd && g_var.redir == 1)
		exit(0);
}

int	exec_cmd(t_parser *parse, t_pipe pip, char *msg)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (ft_check_fork(pid))
		return (pid);
	if (pid == 0)
	{
		//signal(SIGINT, SIGDEL);//SIGNALS
		//signal(SIGQUIT, SIGDEL);
		dp_built(parse, pip, msg);
		path = parse->cmd;
		if (!cmd_slash(parse->cmd))
			path = get_path(parse->cmd, parse);
		if (!path && parse -> my_cmd == 0)
		{
			printf(" ->>> 11imhier\n");
			ft_err("minishell: ", parse->cmd, ": command not found");
		}
		if (parse -> my_cmd == 0)
			ft_execve(path, parse, create_env_arr(env_list_size(g_var.list)));
	}
	return (pid);
}
