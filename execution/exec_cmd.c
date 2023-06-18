/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:02 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/18 17:50:32 by nerrakeb         ###   ########.fr       */
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

void	ft_err(char *s, char *cmd, char *s2)
{
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(s2, STDERR_FILENO);
	exit(127);
}

void	dup_and_exec(t_parser *parse, t_pipe pip, char *msg)
{
	int		*fl;

	fl = fd_redirection(parse);
	if (!fl)
		return ;
	if (!ft_strcmp(msg, "one"))
	{
		parse->fd[1] = 1;
		if (fl[0] != -1)
			parse->fd[0] = fl[0];
		if (fl[1] != -1)
			parse->fd[1] = fl[1];
	}
	else
	{
		parse->fd[1] = pip.wr_end[1];
		parse->fd[0] = 0;
		if (!ft_strcmp(msg, "first"))
		{
			printf("first %s", parse->cmd);
			if (fl[0] != -1)
				parse->fd[0] = fl[0];
			if (fl[1] != -1)
				parse->fd[1] = fl[1];
		}
		if (!ft_strcmp(msg, "last"))
		{
			printf("last %s", parse->cmd);
			parse->fd[1] = 1;
			parse->fd[0] = pip.wr_end[0];
			if (fl[0] != -1)
				parse->fd[0] = fl[0];
			if (fl[1] != -1)
				parse->fd[1] = fl[1];
		}
		if (!ft_strcmp(msg, "between"))
		{
			printf("between %s", parse->cmd);
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
		add = ft_strjoin2(en->env, "=");
		if (!add)
			return (printf("minishell: Memory allocation failed\n"), ft_free(arr), NULL);
		arr[i]= ft_strjoin2(add, en->value);
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
	char	**env;

	pid = fork();
	ft_check(pid);
	if (pid == 0)
	{
		dup_and_exec(parse, pip, msg);
		if (isbuiltin(parse))
		{
			run_builtin(parse);
			exit(g_var.exit_status);
		}
		path = parse->cmd;
		if (!cmd_slash(parse->cmd))
			path = get_path(parse->cmd);
		if (!path)
			ft_err("minishell: ", parse->cmd, ": command not found");
		env = create_env_arr(env_list_size(g_var.list));
		printf("ok\n");
		if (execve(path, table_cmd(parse), env) < 0) //parse->args khass iraj3o **args
		{
			perror("execve");
			exit(1);
		}
	}
	return (pid);
}
