/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/31 22:27:18 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_exec(t_parser *parser, t_data *my_heredoc)
{
	if (!parser)
		return ;
	else if (parser->cmd)
	{
		if (parser->heredoc || parser->infiles || parser->outfiles)
			exec_redir(parser, my_heredoc);
		else
			exec_cmd(parser);
	}
	// else if (tk->type == the_pipe)
	// 	pipe_line();
}
