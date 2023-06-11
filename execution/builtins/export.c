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

int	plus_sign(char *env, char *value)
{
	int	i;
	int	count_plus;

	i = 0;
	count_plus = 0;
	while (env[i])
	{
		if (env[i] == '+')
			count_plus++;
		i++;
	}
	if ((value[0] == '\0' && env[i - 1] == '+') || (env[i - 1] == '+' && count_plus > 1)) //if we don't have the content of the variable env or if we have more than one plus in the end
		return (1);
	return (0);
}

int	check_ident(char *env, char *value, len)
{
	int	i;

	i = 0;
	if (env[0] == '-' && env[i + 1])
	{
		printf("minishell: export: %s: invalid option\n", env);
		printf("export: usage: export [-fn] [name[=value] ...] or export -p\n");
		return (1);
	}
	if (plus_sign(env, value))
		return (printf("minishell: export: `%s': not a valid identifier\n", env));
	while (env[i])
	{
		if (!(ft_isalpha(env[i]) || ft_isdigit(env[i]) || env[i] == '_') && env[len - 1] != '+')
		{
			printf("minishell: export: `%s': not a valid identifier\n", env);
			return (1);
		}
		i++;
	}
	if (i == 0 || !ft_isdigit(str[0])) //if there is an empty string or space or digit in the begining of the word
	{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (1);
	}
	return (0);
}

void	check_export_args(t_env *new_node)
{
	int	len;
	int	check;

	len = ft_strlen(new_node->env);
	check = check_ident(new_node->env, new_node->value, len);
	if (check)
	{
		glb_var.exit_status = 256;
		return (1);
	}
	if (new_node->env[len - 1] == '+')
		concat_value(new_node);
}

void	sh_export(t_parser *parser)
{
	t_data	*tmp;
	t_env	*new_env_node;

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
			if (arg->value[0] == '#' || arg->value[0] == ';')
				break ;
			new_env_node = add_env_node(tmp);
			if (!new_env_node)
				return ;
			check_export_args(new_env_node);
			tmp = tmp->next;
		}
}
