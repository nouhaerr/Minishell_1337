/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:26:24 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/21 21:43:24 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_env(char **e)
{
	int	i;
	int	l;

	i = 0;
	while(e[i][l] != '=')
		l++;
	if (!e[i][l])
		printf("declare -x %s\n", e[i]);
	else
	{
		while(e[i][l] != '=')
		{
			printf("declare -x %c=", e[i][l]);
			l++;
		}	
		print("\"%s\"", e[i][l]);
	}
}

void	sorted_env(void)
{
	char	**env;
	char	*en2;
	char	*tmp;
	int		j;
	int		c;
	int		k;
	int		i;

	i = 0;
	k = 0;
	env = create_env_arr(env_list_size(g_var.list));
	while (env[i])
	{
		c++;
		i++;
	}
	while (k < c - 1)
	{
		j = 0;
		while (j < c - k -1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		k++;
	}
	print_env(env);
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

	tmp = parser->args_exec;
	if (!parser->args_exec)
	{		
		g_var.exit_status = 0;
		sorted_env();
	}
	if (parser->args_exec && parser->args_exec->value[0] == '-' && parser->args_exec->value[1])
	{
		g_var.exit_status = 2;
		printf("minishell: export: %c%c: invalid option\n",
			parser->args_exec->value[0], parser->args_exec->value[1]);
		printf("export: usage: export [-fn] [name[=value] ...] or export -p\n");
	}
	else
		loop_args(tmp);
}
