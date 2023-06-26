/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/26 19:18:43 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isbuiltin(t_parser *parser)
{
	char	*cmd2;

	if (parser->cmd)
	{
		cmd2 = ft_strdup(parser->cmd);
		ft_tolower2(cmd2);
		if (!ft_strcmp(cmd2, "echo") || !ft_strcmp(cmd2, "pwd")
			|| !ft_strcmp(cmd2, "env") || !ft_strcmp(parser->cmd, "unset")
			|| !ft_strcmp(cmd2, "cd") || !ft_strcmp(parser->cmd, "exit")
			|| !ft_strcmp(parser->cmd, "export"))
		{
			free(cmd2);
			return (1);
		}
		free(cmd2);
	}
	return (0);
}

int	exit_status(int status, t_parser *p)
{
	if (p -> my_cmd == 1)
		return (0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

int	ft_ambi(t_data2 *list)
{
	if (list -> amg == 1)
	{
		g_var.exit_status = 1;
		printf ("minishell: %s: ambiguous redirect\n", list->value);
		return (1);
	}
	return (0);
}

void	execution(t_parser *parser)
{
	int		pid;
	t_pipe	pip;
	int		status;
	pid_t	wait_pid;

	pid = 0;
	pip.rd_end = 0;
	pip.wr_end = 0;
	if (!parser)
		return ;
	exec_heredoc(parser);
	if (parser -> signal == 1)
		return ;
	if (parser->cmd && isbuiltin(parser) && parser->next == NULL)
	{
		g_var.parent_process = 1;
		builtin_executor(parser, pip, "one");
	}
	else
	{
		g_var.parent_process = 0;
		if (parser->cmd && parser->next == NULL)
			pid = exec_cmd(parser, pip, "one");
		else
			pid = multiple_pipes(parser);
	}
	while (1)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (parser -> my_cmd == 1)
			g_var.exit_status = 0;
		if (wait_pid == -1)
			break ;
		if (wait_pid == pid)
			g_var.exit_status = exit_status(status, parser);
		if (parser -> my_cmd == 1)
			g_var.exit_status = 0;
	}
}
