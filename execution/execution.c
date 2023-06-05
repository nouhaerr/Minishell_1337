/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/05 19:12:28 by mac              ###   ########.fr       */
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
		return (0);
		free (cmd2);
	}
	free(cmd2);
	return (1);
}

void	execution(t_parser *parser, t_data *my_heredoc)
{
	//int	pid;
	//int	fd[2];

	if (!parser)
		return ;
	else if (parser->next == NULL && parser->cmd && !isbuiltin(parser))
		exec_builtin(parser);
	else if (parser->heredoc || parser->infiles || parser->outfiles)
		exec_redir(parser, my_heredoc);
	// else
	// {
	// else if (parser->next == NULL && parser->cmd)
	// 		exec_cmd(parser, fd);
	// 	else if (parser->next)
	// 		pipe_line();	
	// }
}
