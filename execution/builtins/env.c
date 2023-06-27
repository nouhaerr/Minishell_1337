/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 04:57:29 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/27 17:09:03 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_env(t_data *args)
{
	t_env	*cur;

	cur = g_var.list;
	g_var.exit_status = 0;
	if (args)
	{
		if (args->value[0] == '-' && args->value[1])
		{
			g_var.exit_status = 1;
			printf("env: illegal option -- %c\nusage: env [-iv] \
				[-P utilpath] [-S string] [-u name]\n", args->value[1]);
			printf("\t   [name=value ...] [utility [argument ...]]\n");
		}
		else if (ft_strcmp(args->value, "-"))
		{
			g_var.exit_status = 127;
			printf("env: %s: No such file or directory\n", args->value);
		}
	}
	while (!args && cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->env, cur->value);
		cur = cur->next;
	}
}
