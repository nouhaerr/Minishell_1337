/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/25 18:41:16 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_parser *parser, t_lexer *lexer)
{
	char *str;

	t_data *my_heredoc;

	my_heredoc = NULL;
	while (parser != NULL)
	{
		if (parser -> cmd != NULL)
		{
			if (!ft_strcmp(parser->cmd->value, "pwd"))
				sh_pwd();	
			if (!ft_strcmp(parser->cmd->value, "echo"))
				sh_echo(&parser);
			else if (!ft_strcmp(parser->cmd->value, "exit"))
				sh_exit(parser);
		}
		if (parser -> heredoc != NULL)
		{
			str = her(parser -> heredoc, lexer -> my_env);
			ft_lstaddback2(&my_heredoc, ft_lstnew2(str));
		}
		parser = parser->next;
	}
	while (my_heredoc)
	{
		printf("the value : [%s]", my_heredoc -> value);
		my_heredoc = my_heredoc -> next;
	}
}
