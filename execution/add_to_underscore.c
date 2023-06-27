/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:48:48 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/27 15:35:59 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_to_under_score(t_parser *parser)
{
	char	*str;
	t_env	*node;

	while (parser -> next)
		parser = parser -> next;
	if (parser -> args == NULL)
		str = parser -> cmd;
	else
	{
		while (parser -> args -> next)
			parser -> args = parser -> args -> next;
		str = parser -> args -> value;
	}
	node = ft_getenv(g_var.list, "_");
	if (node != NULL)
	{
		free(node -> value);
		node -> value = ft_strdup(str);
	}
}
