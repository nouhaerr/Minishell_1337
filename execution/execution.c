/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/17 19:32:17 by hobenaba         ###   ########.fr       */
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

// void	switch_pipe(t_pipe *pip, int i, int fd_pip[2][2])
// {
// 	if (i % 2 == 0)
// 	{
		
// 	}
// 	else
// 	{
		
// 	}
// }

// void	open_pipes(t_pipe pip, int index)
// {}

// int	multiple_pipes(t_parser *node)
// {
// 	t_pipe		pip;
// 	int			check;
// 	t_parser	*cur;
// 	pid_t		pid;
// 	int			fd_pip[2][2];

// 	cur = node;
// 	while (cur)
// 	{
// 		switch_pipe(&pip, index, fd_pip);
// 		open_pipes(pip, index);
// 		if (cur == node)
// 			pid = exec_cmd(node, pip, "first");
// 		else if (cur->next == NULL)
// 			pid = exec_cmd(node, pip, "last");
// 		else
// 			pid = exec_cmd(node, pip, "between");
// 		close(pip.rd_end[0]);
// 		close(pip.rd_end[1]);
// 		cur = cur->next;
// 	}
// 	close(pip.wr_end[0]);
// 	close(pip.wr_end[1]);
// 	return (pid);
// }

void	execution(t_parser *parser, t_data *my_heredoc)
{
	int		pid;
	//t_pipe	pip;
	//int		status;

	pid = 0;
	if (!parser)
		return ;
	else if (parser->next == NULL && parser->cmd && !isbuiltin(parser))
	{
		g_var.parent_process = 1;
		exec_builtin(parser);
	}
	else if (parser->heredoc)
		exec_heredoc(parser, &my_heredoc);
	else 
	{
		g_var.parent_process = 0;
		// if (parser->next == NULL && parser->cmd)
		// 	pid = exec_cmd(parser, pip, "one");
		// else
		// 	pid = multiple_pipes(parser);
		// waitpid(pid, &status, 0);
	}
}
