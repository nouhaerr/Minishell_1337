/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:02 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/18 14:27:56 by nerrakeb         ###   ########.fr       */
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

void	dup_and_exec(t_parser *parse, t_pipe pip, char *msg)
{
	int		*fd;

	fd = fd_redirection(parse);
	if (!fd)
		return ;
	parse->fd[1] = pip.wr_end[1];
	parse->fd[0] = 0;
	if (!ft_strcmp(msg, "first"))
	{
		if (fd[0] != -1)
			parse->fd[0] = fd[0];
		if (fd[1] != -1)
			parse->fd[1] = fd[1];
	}
	if (!ft_strcmp(msg, "one") || !ft_strcmp(msg, "last"))
	{
		parse->fd[1] = 1;
		if (!ft_strcmp(msg, "last"))
			parse->fd[0] = pip.rd_end[0];
		if (fd[0] != -1)
			parse->fd[0] = fd[0];
		if (fd[1] != -1)
			parse->fd[1] = fd[1];
	}
	if (!ft_strcmp(msg, "between"))
	{
		parse->fd[0] = pip.rd_end[0];
		parse->fd[1] = pip.wr_end[1];
		if (fd[0] != -1)
			parse->fd[0] = fd[0];
		if (fd[1] != -1)
			parse->fd[1] = fd[1];
	}
	dup2(parse->fd[1], 1);
	dup2(parse->fd[0], 0);
	close(pip.rd_end[0]);
	close(pip.rd_end[1]);
	close(pip.wr_end[0]);
	close(pip.wr_end[1]);
}

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	**create_env_arr(int size)
{
	char	**arr;
	char	*add;
	t_env	*en;
	int		i;

	en = g_var.list;
	i = 0;
	arr = (char **)malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (printf("minishell: Memory allocation failed\n"), NULL);
	while (en)
	{
		add = ft_strjoin(en->env, "=");
		if (!add)
			return (printf("minishell: Memory allocation failed\n"), ft_free(arr), NULL);
		arr[i]= ft_strjoin(add, en->value);
		if (!arr[i])
			return (printf("minishell: Memory allocation failed\n"), ft_free(arr), free(add), NULL);
		free(add);
		en = en->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	exec_cmd(t_parser *parse, t_pipe pip, char *msg)
{
	pid_t	pid;
	char	*path;
	char	*cmd2;

	pid = fork();
	ft_check(pid);
	if (pid == 0)
	{
		dup_and_exec(parse, pip, msg);
		printf("hello\n");
		if (isbuiltin(parse))
		{
			run_builtin(parse);
			exit(g_var.exit_status);
		}
		cmd2 = ft_strdup(parse->cmd);
		ft_tolower2(cmd2);
		path = cmd2;
		if (!cmd_slash(cmd2))
			path = get_path(cmd2);
		if (!path)
			ft_err("minishell: command not found: ", parse->cmd);
		if (execve(path, &cmd2, create_env_arr(env_list_size(g_var.list))) < 0)
		{
			free(cmd2);
			perror("execve");
			exit(1);
		}
		free(cmd2);
	}
	return (pid);
}
