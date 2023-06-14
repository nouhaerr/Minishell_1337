/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:47:29 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/14 07:40:15 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	concat_value(t_env *node)
{
	t_env	*cur;
	char	*str;
	char	*name;

	name = ft_strtrim(node->env, "+");
	if (!name)
		return (1);
	free(node->env);
	node->env = name;
	cur = ft_getenv(glb_var.list, node->env);
	if (cur && cur->value && (node->value[0] == '\0' || !node->value))
		return (1);
	if (cur && node->value[0] != '\0' && ft_strcmp(node->value, "\"\""))
	{
		str = ft_strjoin2(cur->value, node->value);
		if (!str)
			return 1;
		free(node->value);
		node->value = ft_strdup(str);
	}
	return (0);
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
	{
		if (concat_value(new_node))
			return (3);
	}	
	return (0);
}
