/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:54:28 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/26 15:47:19 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H
#include "../includes/env.h"

enum t_enum
{
	word, //0
	the_pipe, // 1
	r_rdr, //2
	dr_rdr, //3
	l_rdr, // 4
	heredoc, //5
} t_enum;

enum t_type
{
	general, //0
	quotes // 1
}	t_type;


typedef struct t_token
{
	char			*value;
	enum t_enum		type;
	enum t_type		arten;
	struct t_token	*next;
}	t_token;

typedef struct t_lexer
{
	int		base;
	int		base2;
	int		her;
	char	*str;
	char	c;
	int		a;
	int		i;
	int		arten;
	t_token	*tokens2;
	t_token	*tok;
}	t_lexer;

// utils i would be in need for my linked list.

t_token	*ft_lstnew(char *value, enum t_enum type, enum t_type arten);
void	ft_lstaddback(t_token **lst, t_token *new);

// funstions related to tokens
int		lex(char *input, t_token **tokens, t_lexer *lexer);
int		check_which_special_char(char c, char next_c, t_token **tokens);
int		ft_ignore_spaces(char *input, int i);
int		other_tokens(t_lexer *lexer, int i, char *input);
int		partition_tokens(t_lexer *lexer, char *input, int i);
int		token_word(char *input, int start, int base);
int		token_env2(char *input, int i, t_lexer *lexer);
int		token_env(char *input, int i, t_lexer *lexer);
int		normal_word(char *input, int start);
int		quotes_word(char *input, int start, int base);
int		env_word(char *input, int start);

// to initiaize 
void	lexer_init(t_lexer *lexer);
#endif