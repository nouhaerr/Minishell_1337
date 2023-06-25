/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:02 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/25 21:28:51 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_fd(int *fl, t_parser *parse)
{
	if (fl[0] != -1)
		parse->fd[0] = fl[0];
	if (fl[1] != -1)
		parse->fd[1] = fl[1];
}

int	*dup_fd(t_parser *parse, t_pipe pip, char *msg)
{
	int		*fl;

	fl = fd_redirection(parse);
	if (!fl)
		return (0);
	parse->fd[1] = 1;
	if (!ft_strcmp(msg, "one"))
	{
		parse->fd[0] = 0;
		ft_fd(fl, parse);
	}
	else
	{
		parse->fd[1] = pip.wr_end[1];
		parse->fd[0] = 0;
		if (!ft_strcmp(msg, "first"))
			ft_fd(fl, parse);
		if (!ft_strcmp(msg, "last"))
		{
			parse->fd[1] = 1;
			parse->fd[0] = pip.rd_end[0];
			ft_fd(fl, parse);
		}
		if (!ft_strcmp(msg, "between"))
		{
			parse->fd[0] = pip.rd_end[0];
			parse->fd[1] = pip.wr_end[1];
			ft_fd(fl, parse);
		}
	}
	// printf("->>> %d\t%d\n", parse->fd[0], parse -> fd[1]);
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

	check_dir_notexec(path);
	arr = table_cmd(node);
	//printf("HERE %s\n", *arr); // && access(path, X_OK | F_OK)
	if (execve(path, arr, env) < 0)
	{
		free(env);
		perror("minishell");
		// if (cmd_slash(node->cmd))
		// 	ft_err("minishell: ", node->cmd, ": No such file or directory");
		exit(127);
	}
	free(env);
}

void	dp_built(t_parser *parse, t_pipe pip, char *msg)
{
	if (!dup_fd(parse, pip, msg))
		exit(1);
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
		signal(SIGINT, SIG_DFL);//SIGNALS
		signal(SIGQUIT, SIG_DFL);
		dp_built(parse, pip, msg);
		path = parse->cmd;
		if (!cmd_slash(parse->cmd))
			path = get_path(parse->cmd, parse);
		if (!path && parse -> my_cmd == 0)
		{
			g_var.exit_status = 127;
			ft_err("minishell: ", parse->cmd, ": command not found");
		}
		if (parse -> my_cmd == 0)
			ft_execve(path, parse, create_env_arr(env_list_size(g_var.list)));
	}
	return (pid);
}
