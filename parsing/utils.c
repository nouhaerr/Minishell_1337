/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:18:35 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/25 18:54:02 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ignore_spaces(char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}

void	check_amg_parse(t_token *t2, t_lexer *l)
{
	if (t2 != NULL && t2->arten == env_general
		&& (t2->next != NULL && t2->next->arten == env_general))
			l -> amg = 1;
	if (!ft_strcmp(t2 -> value, " "))
		l -> amg = 1;
}

int	ft_lstsize_parse(t_parser *parse)
{
	int	i;

	i = 0;
	if (!parse)
		return (0);
	while (parse)
	{
		i++;
		parse = parse->next;
	}
	return (i);
}

// this one to check the output of my main struct
void	check_struct(t_parser *parser)
{
	int i;

	i = 0;
	while (parser)
	{	
		t_data2 *out = parser->outfiles;
		t_data2 *in = parser->inf_her;
		t_data *args = parser->args;
		char *cmd = parser->cmd;
		printf("struct number %d\n\n", ++i);
		while (out)
		{
			printf("[out : %s, type : %d == amg : %d] \n"
			, (out)->value, (out)->type, out -> amg);
			(out) = (out)->next;
		}
		while (in)
		{
			printf("infher : [%s]  type %d == ->>>> amg %d\n "
		, (in)->value, in -> type, in -> amg);
			(in) = (in)->next;
		}
		printf("cmd: [%s]\n", cmd);
		while (args)
		{
			printf("args : [%s]\n", (args)->value);
			(args) = (args)->next;
		}
		printf("my_cmd [[[%d]]] address == %p\n", parser -> my_cmd, parser);
		parser = parser->next;
	}
}
