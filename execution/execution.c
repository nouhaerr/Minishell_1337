/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/01 13:49:32 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution(t_parser *parser, t_data *my_heredoc)
{
	if (!parser)
		return ;
	else
	{
		if (parser->heredoc || parser->infiles || parser->outfiles)
			exec_redir(parser, my_heredoc);
		else
			exec_cmd(parser);
	}
	// else if (tk->type == the_pipe)
	// 	pipe_line();
}
