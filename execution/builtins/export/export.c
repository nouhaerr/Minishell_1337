/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:26:24 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/21 18:40:43 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_env()
{
	t_env	*cur;

	cur = g_var.list;
	while (cur)
	{
		if (!cur->value)
			printf("declare -x %s\n", cur->env);
		else
			printf("declare -x %s=\"%s\"\n", cur->env, cur->value);
		cur = cur->next;
	}
}

void	sorted_env(void)
{
	char	**env;
	char	*en2;
	char	*tmp;
	int		j;
	int		l;
	int		k;
	int		i;

	i = 0;
	env = create_env_arr(env_list_size(g_var.list));
	while (env[i])
	{
		j = i + 1;
		while (env[i][l] != '=')
			l++;
		while (env[j])
		{
			k = 0;
			while (env[j][k] != '=')
				k++;
			if (ft_strcmp(env[i]))
			j++;
		}
		e = e->next;
	}
	print_env();
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
		env_value = NULL;
	else if (arg->value[i + 1] == '\0')
	{
		env_value = ft_strdup("");
		len1 = len - ft_strlen(&arg->value[i]);
	}
	else
	{
		env_value = ft_strdup(&arg->value[i] + 1);
		len1 = len - ft_strlen(&arg->value[i]);
	}
	return (ft_lstnew_env(ft_substr(arg->value, 0, len1), env_value));
}

void	loop_args(t_data *tmp)
{
	t_env	*new_env_node;
	int		j;

	while (tmp)
	{
		if (check_egal(tmp))
		{
			tmp = tmp->next;
			continue ;
		}
		new_env_node = subargs_to_env_node(tmp);
		if (!new_env_node)
			return ;
		j = check_export_args(new_env_node);
		if (j == 2 || j == 3)
		{
			tmp = tmp->next;
			continue ;
		}
		modifie_and_add(new_env_node);
		tmp = tmp->next;
	}
}

void	sh_export(t_parser *parser)
{
	t_data	*tmp;

	tmp = parser->args;
	if (!parser->args)
	{		
		g_var.exit_status = 0;
		sorted_env();
	}
	if (parser->args && parser->args->value[0] == '-' && parser->args->value[1])
	{
		g_var.exit_status = 2;
		printf("minishell: export: %c%c: invalid option\n",
			parser->args->value[0], parser->args->value[1]);
		printf("export: usage: export [-fn] [name[=value] ...] or export -p\n");
	}
	else
		loop_args(tmp);
}
