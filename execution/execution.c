make/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/24 17:56:00 by hobenaba         ###   ########.fr       */
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

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return(WTERMSIG(status) + 128);
	return (0);
}

int	ft_ambi(t_data2 *list)
{
	if (list -> amg == 1)
	{
		g_var.exit_status = 1;
		printf ("minishell: : ambiguous redirect\n");
		return (1);
	}
	return(0);
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
	if (parser != NULL && parser->cmd && isbuiltin(parser) && parser->next == NULL)
	{
		g_var.parent_process = 1;
		builtin_executor(parser, pip, "one");
	}
	else
	{   
		g_var.parent_process = 0;
		if (parser->cmd && ft_lstsize_parse(parser) == 1)
			pid = exec_cmd(parser, pip, "one");
		else
		{
			pid = multiple_pipes(parser);
		}
	}
		// check multiple pipes limits
	while (1)
	{
		wait_pid = waitpid(-1, &status, 0); // If pid is -1, the call waits for any child process.
		if (wait_pid == -1) // If there are no children not previously awaited, -1 is returned with errno set to [ECHILD].
			break ;
		if (wait_pid == pid) // last child pid
			g_var.exit_status = exit_status(status);
	}
}
