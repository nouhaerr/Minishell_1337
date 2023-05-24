/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:54:36 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 10:36:32 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum t_e
{
	clear, // >
	finish_up, // >>
	word_general = 0,
	d_q = 7,
	s_q = 8 // i  dont now if i need those both enums now.
} t_e;

typedef struct t_data
{
	char			*value;
	struct t_data	*next;
}	t_data;

// this one im gonna use ft_lstnew and back others ft_lstnew2 // 

typedef struct t_data2
{
	char 			*value;
	enum t_e		type;
	struct t_data2	*next;
} t_data2;


// this represent the main struct that i will send to my teammate
typedef struct t_parser
{
	t_data			*cmd;
	t_data2			*args;
	t_data2			*outfiles;
	t_data			*infiles;
	t_data			*heredoc;
	int				exit_status;
	struct t_parser	*next;
} t_parser;

t_parser	glb_var;

// functions im gonna work with
void	parse(t_token **tokens, t_parser **parser);
void	create_node(t_parser *parser, char *next_value, int type, int i);
t_token	*my_next_word(t_token *tokens);

// utils to help me 
int		ft_lstsize_parse(t_parser *parse);
void	check_struct(t_parser *parser);

t_data		*ft_lstnew2(char *value);
void		ft_lstaddback2(t_data **lst, t_data *new);
t_parser	*ft_lstnew3(void);
t_parser	*ft_lstaddback3(t_parser **lst, t_parser *new);
t_data2		*ft_lstnew4(char *value, enum t_e type);
void		ft_lstaddback4(t_data2 **lst, t_data2 *new);

#endif
