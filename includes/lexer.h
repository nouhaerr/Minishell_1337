/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:54:28 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 10:39:05 by nerrakeb         ###   ########.fr       */
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
	char *value;
	enum t_enum type;
	enum t_type arten;
	struct t_token *next;
}	t_token;

// utils i would be in need for my linked list.

t_token *ft_lstnew(char *value, enum t_enum type, enum t_type arten);
void	ft_lstaddback(t_token **lst, t_token *new);
int     ft_ignore_spaces(char *input, int i);

// funstions related to tokens
int token(char *input, t_token **tokens, t_env *my_envs, int exit_status);
int check_which_special_char(char c, char next_c, t_token **tokens);

#endif