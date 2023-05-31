/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:14:51 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/30 16:49:27 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_node(t_parser *parser, t_lexer *lexer)
{
	if (lexer -> i == 0 && (lexer->tokens2->type == word))
		parser -> cmd = ft_strdup(lexer -> tok -> value);
	else if (lexer->tokens2->type == word)
		ft_lstaddback2(&(parser->args), ft_lstnew2(lexer -> tok -> value));
	else if (lexer->tokens2->type == l_rdr)
		ft_lstaddback2(&(parser->infiles), ft_lstnew2(lexer -> tok -> value));
	else if (lexer->tokens2->type == r_rdr)
		ft_lstaddback4(&(parser->outfiles),
			ft_lstnew4(lexer -> tok -> value, clear));
	else if (lexer->tokens2->type == dr_rdr)
		ft_lstaddback4(&(parser->outfiles),
			ft_lstnew4(lexer -> tok -> value, finish_up));
	else if (lexer->tokens2->type == heredoc && lexer->tok ->arten == general)
		ft_lstaddback4(&(parser->heredoc),
			ft_lstnew4(lexer -> tok -> value, expand));
	else if (lexer->tokens2->type == heredoc && lexer->tok ->arten == quotes)
		ft_lstaddback4(&(parser->heredoc),
			ft_lstnew4(lexer -> tok -> value, not_expand));
}

t_parser	*build_list_parser(t_parser **parser, t_lexer *lexer, t_parser *t)
{
	if (((lexer->tokens2)->type) == the_pipe)
	{
		lexer->i = 0;
		t = ft_lstaddback3(parser, ft_lstnew3());
		lexer->tokens2 = (lexer->tokens2)->next;
	}
	lexer->tok = my_next_word(lexer->tokens2);
	create_node(t, lexer);
	return (t);
}

void	parse(t_token **tokens, t_parser **parser, t_lexer *lexer)
{
	t_parser	*t;

	lexer->tokens2 = *tokens;
	if ((lexer->tokens2) != NULL)
		t = ft_lstaddback3(parser, ft_lstnew3());
	lexer->i = 0;
	while (lexer->tokens2)
	{
		t = build_list_parser(parser, lexer, t);
		if ((lexer->tokens2)->type == l_rdr || (lexer->tokens2)->type == r_rdr \
		|| (lexer->tokens2)->type == dr_rdr \
		|| (lexer->tokens2)->type == heredoc)
			lexer->tokens2 = lexer->tok->next;
		else if ((lexer->tokens2)->type == word)
		{
			lexer->tokens2 = (lexer->tokens2)->next;
			lexer->i++;
		}
	}
	//check_struct(*parser);
}
// just to check on if my parsing is doing alright.

t_token	*my_next_word(t_token *tokens)
{
	t_token	*t;

	t = tokens;
	while (tokens)
	{
		if (tokens->type == word)
			return (tokens);
		tokens = tokens->next;
	}
	return (t);
}