/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 04:57:29 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/24 15:51:44 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	path_not_found(void)
{
	ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		glb_var.exit_status = 127;
	return ;
}

void	sh_env(t_env *env_cmd)
{
	int	path_found;
	t_env	*cur;

	cur = env_cmd;
	path_found = 0;
	while (cur)
	{
		if (ft_strncmp(cur->env, "PATH=", 5))
		{
			path_found = 1;
			break ;
		}
		cur = cur->next;
	}
	if (path_found)
		path_not_found();
	cur = env_cmd;
	while (cur)
	{
		printf("%s=%s\n", cur->env, cur->value);
		cur = cur->next;
	}	
}
