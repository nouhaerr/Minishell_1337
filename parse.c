/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:14:51 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/23 21:33:07 by hobenaba         ###   ########.fr       */
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
void parse(t_token **tokens, t_parser **parser)
{
	t_parser *t;
	t_token *tok;
	t_token *tokens2;
	int i;

	tokens2 = *tokens;
	if ((tokens2) != NULL)
		t = ft_lstaddback3(parser, ft_lstnew3());
	i = 0;
	while (tokens2)
	{	
		if (((tokens2) -> type) == the_pipe)
		{
			i = 0;
			t = ft_lstaddback3(parser, ft_lstnew3());
			tokens2 = (tokens2) -> next;
		}
		tok = my_next_word(tokens2);	
		create_node(t, tok -> value, (tokens2) -> type, i);
		if ((tokens2) -> type == l_rdr || (tokens2) -> type == r_rdr || (tokens2) -> type == dr_rdr || (tokens2) -> type == heredoc)
			tokens2 = tok -> next;
		else if ((tokens2) -> type == word)
		{
			tokens2  = (tokens2) -> next;
			i++;
		}
	}
	// just to check on if my parsing is doing alright.
	check_struct(*parser);
	
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