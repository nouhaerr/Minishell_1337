/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:54:36 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/15 11:51:43 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum	t_e
{
	expand,
	not_expand,
	clear, // (Trunc) outfile normal >
	finish_up // append >>
} t_e;

typedef struct t_data
{
	char			*value;
	int				fd;
	char			*error;
	struct t_data	*next;
}	t_data;

typedef struct t_data2
{
	char			*value;
	int				fd;
	char			*error;
	enum t_e		type;
	struct t_data2	*next;
}	t_data2;

// this represent the main struct that i will send to my teammate
typedef struct t_parser
{
	char			*cmd;
	t_data			*args;
	t_data2			*outfiles;
	t_data			*infiles;
	t_data2			*heredoc;
	struct t_parser	*next;
}	t_parser;

// functions im gonna work with in the parsing part
void		parse(t_token **tokens, t_parser **parser, t_lexer *lexer);
void		create_node(t_parser *parser, t_lexer *lexer);
t_token		*my_next_word(t_token *tokens);
int			ft_lstsize_parse(t_parser *parse);
void		check_struct(t_parser *parser);

// those are relate to then creation of my lists that im gonna work with.

t_data		*ft_lstnew2(char *value);
void		ft_lstaddback2(t_data **lst, t_data *new);
t_parser	*ft_lstnew3(void);
t_parser	*ft_lstaddback3(t_parser **lst, t_parser *new);
t_data2		*ft_lstnew4(char *value, enum t_e type);
void		ft_lstaddback4(t_data2 **lst, t_data2 *new);

// functions that are responsible for freeing my list

void		free_mylist(void *list, int type);

#endif