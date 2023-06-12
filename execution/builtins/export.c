/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:26:24 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/12 02:30:26 by nerrakeb         ###   ########.fr       */
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
				if (!cur->value[0])
					printf("declare -x %s\n", cur->env);
				else if (!ft_strcmp(cur->value, "\"\""))
					printf("declare -x %s=%s\n", cur->env, cur->value);
				else
					printf("declare -x %s=\"%s\"\n", cur->env, cur->value);
			}
			cur = cur->next;
		}
		i++;
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
	return (0);
	// if (new_node->env[len - 1] == '+')
	// 	concat_value(new_node);
}

t_env	*subargs_to_env_node(t_data *arg)
{
	t_env	*new;
	char	*env_value;
	int		len;
	int		len1;
	int		i;

	i = 0;
	len = ft_strlen(arg->value);
	len1 = len;
	while (arg->value[i] != '=' && arg->value[i])
		i++;
	if (arg->value[i] == '\0')
		env_value = ft_strdup("");
	else if (arg->value[i + 1] == '\0')
	{
		env_value = ft_strdup("\"\"");
		len1 = len - ft_strlen(&arg->value[i]);
	}
	else
	{
		env_value = ft_strdup(&arg->value[i] + 1);
		len1 =  len - ft_strlen(&arg->value[i]);
	}
	if (arg->value[0] == '=' || !ft_strcmp(arg->value, "=") || !arg->value[0])
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg->value);
		glb_var.exit_status = 1;
	}
	if (!env_value)
		return (NULL);
	new = ft_lstnew_env(ft_substr(arg->value, 0, len1), env_value);
	printf("env :%s: et le contenu :%s:\n", new->env, new->value);
	return (new);
}
void	sh_export(t_parser *parser)
{
	t_data	*tmp;
	t_env	*new_env_node;

	tmp = parser->args;
	if (!parser->args || (parser->args && (parser->args->value[0] == '#' || parser->args->value[0] == ';')))
	{
		if (parser->args && parser->args->value[0] == ';' && parser->args->value[1])
		{
			sorted_env();
			printf("minishell: %s: command not found\n", &parser->args->value[1]);
			glb_var.exit_status = 127;
		}
		else
		{
			sorted_env();
			glb_var.exit_status = 0;
		}
	}
	else
	{
		while (tmp)
		{
			if (tmp->value[0] == '#' || tmp->value[0] == ';')
			{
				glb_var.exit_status = 0;
				// sorted_env(parser->args);
				if (tmp->value[0] == ';' && tmp->value[1])
				{
					printf("minishell: %s: command not found\n", &tmp->value[1]);
					glb_var.exit_status = 127;
				}
				break ;
			}
			// if (tmp->value[0] == '=' || !ft_strcmp(tmp->value, "=") || !tmp->value[0])
			// {
			// 	printf("minishell: export: `%s': not a valid identifier\n", tmp->value);
			// 	glb_var.exit_status = 1;
			// 	return ;
			// }
			new_env_node = subargs_to_env_node(tmp);
			if (!new_env_node)
				return ;
			int lk = check_export_args(new_env_node);
			if (lk == 1)
				break ;
			else if (lk == 2)
				return ;
			ft_lstaddback_env(&glb_var.list, new_env_node);
			tmp = tmp->next;
		}
	}
}
