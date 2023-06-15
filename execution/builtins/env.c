/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 04:57:29 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/15 08:05:03 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	path_not_found(void)
{
	ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		glb_var.exit_status = 127;
	return ;
}

void	sh_env(void)
{
	int		path_found;
	t_env	*cur;

	cur = glb_var.list;
	path_found = 0;
	while (cur)
	{
		if (!ft_strcmp(cur->env, "PATH"))
		{
			path_found = 1;
			break ;
		}
		cur = cur->next;
	}
	if (!path_found)
	{
		path_not_found();
		return ;
	}
	cur = glb_var.list;
	while (cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->env, cur->value);
		cur = cur->next;
	}
}
