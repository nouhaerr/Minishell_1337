/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:02 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/25 20:05:12 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execve(char *path, t_parser *node, char **env)
{
	char	**arr;

	check_dir_notexec(path, node);
	arr = table_cmd(node);
	// && access(path, X_OK | F_OK)
	if (execve(path, arr, env) < 0)
	{
		free(env);
		if (!ft_strcmp(node->cmd, ""))
		{
			g_var.exit_status = 127;
			ft_err("minishell: ", node->cmd, ": command not found");
		}
		perror("minishell");
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
		//signal(SIGINT, SIG_DFL);
		//signal(SIGQUIT, SIG_DFL);
		dp_built(parse, pip, msg);
		path = parse->cmd;
		if (!cmd_slash(parse->cmd))
			path = get_path(parse->cmd);
		if (!path && parse->my_cmd == 0)
		{
			g_var.exit_status = 127;
			ft_err("minishell: ", parse->cmd, ": command not found");
		}
		if (parse -> my_cmd == 0)
			ft_execve(path, parse, create_env_arr(env_list_size(g_var.list)));
	}
	return (pid);
}
