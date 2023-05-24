/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:53:34 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 18:14:10 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int check_which_special_char(char c, char next_c, t_token **tokens)
{
	if (c == '|')
		return (ft_lstaddback(tokens, ft_lstnew(ft_strdup("|"), the_pipe, general)), 1);
	else if (c == '>')
	{
		if (next_c == '>')
			return (ft_lstaddback(tokens, ft_lstnew(ft_strdup(">>"), dr_rdr, general)), 2);
		return (ft_lstaddback(tokens, ft_lstnew(ft_strdup(">"), r_rdr, general)), 1);
	}
	else if(c == '<')
	{
		if (next_c == '<')
			return (ft_lstaddback(tokens, ft_lstnew(ft_strdup("<<"), heredoc, general)), 2);
		return (ft_lstaddback(tokens, ft_lstnew(ft_strdup("<"), l_rdr, general)), 1);
	}	
	return(0);	
}

void build_list(t_lexer *lexer, t_token **tokens)
{
	int arten;
	
	if(lexer -> base2 != 0)
		arten = quotes;
	else
		arten = general;
	ft_lstaddback(tokens, ft_lstnew(lexer -> str, word, arten));
	lexer -> str = NULL;
	lexer -> base2 = 0;
}

int lex(char *input, t_token **tokens, t_lexer *lexer, int exit_status)
{
	int i;

	i = 0;
	lexer_init(lexer);
	while (input[i])
	{
		if (input[i] == ' ')
			i = ft_ignore_spaces(input, i);
		if (ft_strchr("$|><", input[i]) != NULL && lexer -> base == 0)
		{
			if (input[i] == '<' && input[i + 1] == '<')
				lexer -> her = 1;
			i += check_which_special_char(input[i],input[i + 1], tokens);
		}
		else
			i = partition_tokens(lexer, input, i);
		if (input[i] == '$')
            i = token_env(input, i, lexer, exit_status);
		if (lexer -> str != NULL && (input [i] == '\0' || ft_strchr(" |><", input[i]) != NULL))
			build_list(lexer, tokens);
	}
	return (lexer -> base);
}