/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:18:35 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 10:55:22 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_ignore_spaces(char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++; 
	return (i);
}

void	free_my_struct(t_token *tokens)
{
	while (tokens)
	{
		free(tokens);
		tokens = tokens -> next;
	}
}
