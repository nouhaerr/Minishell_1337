/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:26:24 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/13 08:26:48 by nerrakeb         ###   ########.fr       */
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

t_env	*subargs_to_env_node(t_data *arg)
{
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
	if (!env_value)
		return (NULL);
	return (ft_lstnew_env(ft_substr(arg->value, 0, len1), env_value));
}

void	modifie_env_node(char *env, char *new_value)
{
	t_env	*cur;
	(void)new_value;

	cur = glb_var.list;
	while (cur)
	{
		if (!ft_strcmp(cur->env, env))
		{
			free(cur->value);
			if (new_value)
			{
				printf("ok\n");
				cur->value = ft_strdup(new_value);
			}
			else
				cur->value = 0;
			return ;
		}
		cur = cur->next;
	}
}

void	check_and_add(t_env *new_env_node)
{
	if (env_search(glb_var.list, new_env_node->env))
	{
		modifie_env_node(new_env_node->env, new_env_node->value);
		free(new_env_node->env);
		return (free(new_env_node->value));
	}
	ft_lstaddback_env(&glb_var.list, new_env_node);
}

void	loop_args(t_parser *parser)
{
	t_data	*tmp;
	t_env	*new_env_node;
	int		j;

	tmp = parser->args;
	while (tmp)
	{
		if (tmp->value[0] == '=' || !ft_strcmp(tmp->value, "=") || !tmp->value[0])
		{
			printf("minishell: export: `%s': not a valid identifier\n", tmp->value);
			glb_var.exit_status = 1;
			tmp = tmp->next;
			continue ;
		}
		new_env_node = subargs_to_env_node(tmp);
		if (!new_env_node)
			return ;
		j = check_export_args(new_env_node);
		if (j == 1)
			break ;
		else if (j == 2)
		{
			tmp = tmp->next;
			continue ;
		}
		check_and_add(new_env_node);
		tmp = tmp->next;
	}
}

void	sh_export(t_parser *parser)
{
	
	if (!parser->args)
	{		
		glb_var.exit_status = 0;
		sorted_env();
	}
	else
		loop_args(parser);
}
