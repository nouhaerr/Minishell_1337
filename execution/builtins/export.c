/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:26:24 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/01 03:26:25 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sorted_env(void)
{
	t_env	*cur;
	char	*str;
	int	i;

	i = 0;
	str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
	while (str[i])
	{
		cur = glb_var.list;
		while (cur)
		{
			if (cur->env[0] == str[i])
			{
				if (!cur->value)
					printf("declare -x %s\n", cur->env);
				else
					printf("declare -x %s=\"%s\"\n", cur->env, cur->value);
			}
			cur = cur->next;
		}
		i++;
	}	
}

void	export_args(t_data *arg)
{
	glb_var.exit_status = 0;
	if (arg->value[0] == '#' || arg->value[0] == ';')
		break ;
}

void	sh_export(t_parser *parser)
{
	t_data	*tmp;

	tmp = parser->args;
	if (!parser->args || (parser->args && (parser->args->value[0] == '#' || parser->args->value[0] == ';'))
	{
		sorted_env();
		glb_var.exit_status = 0;
	}
	else
	{
		while (tmp)
		{
			export_args(tmp);
			tmp = tmp->next;
		}
}
