/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/17 11:47:54 by nerrakeb         ###   ########.fr       */
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

// int	multiple_pipes(t_parser *node)
// {
// 	int			fd[2];
// 	int			pid;
// 	t_parser	*cur;

// 	cur = node;
// 	while (cur)
// 	{
// 		pipe(fd);
// 		if (cur == node)
// 			pid = exec_cmd(node, fd, "one");
// 		else if (cur->next == NULL)
// 			pid = exec_cmd(node, fd, "last");
// 		else
// 			pid = exec_cmd(node, fd, "between");
// 		close(fd[0]);
// 		close(fd[1]);
// 		cur = cur->next;
// 	}
// 	return (pid);
// }

void	execution(t_parser *parser, t_data *my_heredoc)
{
	// int	pid;
	// int	status;
	// int	*fd;

	// pid = 0;
	// fd = NULL;
	if (!parser)
		return ;
	else if (parser->next == NULL && parser->cmd && !isbuiltin(parser))
	{
		// g_var.parent_process = 1;
		exec_builtin(parser);
	}
	else if (parser->heredoc)
		exec_heredoc(parser, my_heredoc);
	// else if (parser->next == NULL && parser->cmd)
	// {
	// 	g_var.parent_process = 0;
	// 	//pid = exec_cmd(parser, fd, "one");
	// //	else if (parser->next)
	// // 		pid = multiple_pipes(parser);
	// 	waitpid(pid, &status, 0);
	// }
}
