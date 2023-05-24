/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:14:51 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 17:08:26 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void create_node(t_parser *parser, char *next_value, int type, int i)
{
	
	if (i == 0 && (type == word))
		ft_lstaddback2(&(parser ->cmd), ft_lstnew2(next_value));
	else if (type == word)
		ft_lstaddback2(&(parser ->args), ft_lstnew2(next_value));
	else if (type == l_rdr)
		ft_lstaddback2(&(parser ->infiles), ft_lstnew2(next_value));
	else if (type == r_rdr)
		ft_lstaddback4(&(parser ->outfiles), ft_lstnew4(next_value, clear));
	else if (type == dr_rdr)
		ft_lstaddback4(&(parser ->outfiles), ft_lstnew4(next_value, finish_up));
	else if (type == heredoc)
		ft_lstaddback2(&(parser ->heredoc), ft_lstnew2(next_value));
}

t_parser *build_list_parser(t_parser **parser, t_lexer *lexer, t_parser *t)
{
	if (((lexer ->tokens2) -> type) == the_pipe)
	{
		lexer ->i = 0;
		t = ft_lstaddback3(parser, ft_lstnew3());
		lexer -> tokens2 = (lexer -> tokens2) -> next;
	}
	lexer ->tok = my_next_word(lexer ->tokens2);	
	create_node(t, lexer -> tok -> value, (lexer -> tokens2) -> type, lexer ->i);
	return (t);
}

void parse(t_token **tokens, t_parser **parser, t_lexer *lexer)
{
	t_parser *t;

	lexer -> tokens2 = *tokens;
	if ((lexer -> tokens2) != NULL)
		t = ft_lstaddback3(parser, ft_lstnew3());
	lexer -> i = 0;
	while (lexer -> tokens2)
	{	
		t = build_list_parser(parser, lexer, t);
		if ((lexer -> tokens2) -> type == l_rdr || (lexer -> tokens2) -> type == r_rdr || (lexer -> tokens2) -> type == dr_rdr || (lexer -> tokens2) -> type == heredoc)
			lexer -> tokens2 = lexer -> tok -> next;
		else if ((lexer -> tokens2) -> type == word)
		{
			lexer -> tokens2  = (lexer -> tokens2) -> next;
			lexer -> i++;
		}
	}
	// just to check on if my parsing is doing alright.
	//check_struct(*parser);
}

t_token *my_next_word(t_token *tokens)
{
	t_token *t;

	t = tokens;
	while (tokens)
	{
		if (tokens -> type == word)
			return (tokens);
		tokens = tokens -> next;
	}
	return (t);
}
