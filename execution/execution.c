/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:37:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/30 19:41:03 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_exec(t_parser *parser, t_token *tk)
{
	if (!parser)
		return ;
	else if (tk->type == the_pipe)
		pipe_line();
	else if (tk->type == word)
		exec_cmd(parser);
}
