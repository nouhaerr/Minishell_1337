/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/09 22:24:37 by nerrakeb         ###   ########.fr       */
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

void	multiple_pipes(t_parser *node)
{
	int			fd[2];
	t_parser	*cur;

	cur = node;
	while (cur)
	{
		pipe(fd);
		if (cur == node)
			exec_cmd(node, "one");
		else if (cur->next == NULL)
			exec_cmd(node, "last");
		else
			exec_cmd(node, "between");
		cur = cur->next;
	}
}

void	execution(t_parser *parser, t_data *my_heredoc)
{
	//int	pid;
	// int	*fd;

	if (!parser)
		return ;
	else if (parser->next == NULL && parser->cmd && !isbuiltin(parser))
		exec_builtin(parser);
	else if (parser->heredoc)
		exec_redir(parser, my_heredoc);
	// else
	// {
	// 	if (parser->next == NULL && parser->cmd)
	// 		exec_cmd(parser, fd, "one");
	//	else if (parser->next)
	// 		multiple_pipes(parser);
	// }
	// 
}
