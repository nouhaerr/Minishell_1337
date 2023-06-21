/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:18:35 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/21 18:58:15 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ignore_spaces(char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}

// functions that helped me to check on my code and debugg it and nothing else
// this function is just to guide me// no need of it in the code itself
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
		printf("struct number %d\n", ++i);
		while (out)
		{
			printf("[out : %s, type : %d]\n", (out)->value, (out)->type);
			(out) = (out)->next;
		}
		while (in)
		{
			printf("infher : [%s]\n  type %d\n", (in)->value, in -> type);
			(in) = (in)->next;
		}
		printf("cmd: [%s]\n", cmd);
		while (args)
		{
			printf("args : [%s]\n", (args)->value);
			(args) = (args)->next;
		}
		parser = parser->next;
	}
}
