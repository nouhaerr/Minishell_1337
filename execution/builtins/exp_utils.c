/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:47:29 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/13 08:41:37 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	concat_value(t_env *node)
{
	t_env	*cur;
	char	*str;
	char	*name;

	name = ft_strtrim(node->env, "+");
	if (!name)
		return ;
	free(node->env);
	node->env = name;
	cur = glb_var.list;
	if (env_search(cur, node->env) && node->value[0] != '\0' && ft_strcmp(node->value, "\"\""))
	{
		str = ft_strjoin2(cur->value, node->value);
		if (!str)
			return ;
		free(cur->value);
		cur->value = ft_strdup(str);
	}
}

int	check_export_args(t_env *new_node)
{
	int	len;
	int	check;

	len = ft_strlen(new_node->env);
	check = check_ident(new_node->env, new_node->value, len);
	if (check)
	{
		glb_var.exit_status = 1;
		if (check == 3)
		{
			glb_var.exit_status = 2;
			return (1);
		}
		return (2);
	}
	if (new_node->env[len - 1] == '+')
		concat_value(new_node);
	return (0);
}
