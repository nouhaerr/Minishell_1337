/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/17 20:39:30 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isbuiltin(t_parser *parser)
{
	char	*cmd2;

	cmd2 = ft_strdup(parser->cmd);
	ft_tolower2(cmd2);
	if (ft_strcmp(cmd2, "echo") || ft_strcmp(cmd2, "pwd")
		|| ft_strcmp(cmd2, "env") || ft_strcmp(parser->cmd, "unset")
		|| ft_strcmp(cmd2, "cd") || ft_strcmp(parser->cmd, "exit"))
	{
		free(cmd2);
		return (0);
	}
	free(cmd2);
	return (1);
}

void	execution(t_parser *parser, t_data *my_heredoc)
{
	int		pid;
	t_pipe	pip;
	int		status;

	pid = 0;
	pip.rd_end = 0;
	pip.wr_end = 0;
	if (!parser)
		return ;
	else if (parser->next == NULL && parser->cmd && !isbuiltin(parser))
	{
		g_var.parent_process = 1;
		run_builtin(parser);
	}
	else if (parser->heredoc)
		exec_heredoc(parser, &my_heredoc);
	else 
	{
		g_var.parent_process = 0;
		if (parser->next == NULL && parser->cmd)
			pid = exec_cmd(parser, pip, "one");
		else
			pid = multiple_pipes(parser);
		waitpid(pid, &status, 0);
	}
	free_mylist(my_heredoc, 2);
}
