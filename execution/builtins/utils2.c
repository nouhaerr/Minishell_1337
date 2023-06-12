/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 01:33:01 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/12 02:28:29 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_ident(char *env, char *value, int len)
{
	int	i;

	i = 0;
	(void)len;
	// if (arg->value[0] == '=' || !ft_strcmp(arg->value, "=") || !arg->value[0])
	// {
	// 	printf("minishell: export: `%s': not a valid identifier\n", arg->value);
	// 	glb_var.exit_status = 1;
	// 	return NULL;
	// }
	if(!env && !value)
		return (1);
	if (env[0] == '-' && env[i + 1])
	{
		printf("minishell: export: %s: invalid option\n", env);
		printf("export: usage: export [-fn] [name[=value] ...] or export -p\n");
		return (3);
	}
	if (ft_isdigit(env[0])) //if there is an empty string or space or digit in the begining of the word
	{
			printf("minishell: export: `%s': not a valid identifier\n", env);
			return (1);
	}
	if (plus_sign(env, value))
		return (printf("minishell: export: `%s': not a valid identifier\n", env)); //&& env[len - 1] == '+'
	while (env[i])
	{
		if (!(ft_isalpha(env[i]) || ft_isdigit(env[i]) || env[i] == '_') && env[len - 1] != '+')
		{
			printf("minishell: export: `%s': not a valid identifier\n", env);
			return (1);
		}
		i++;
	}
	return (0);
}
