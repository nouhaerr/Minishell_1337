/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:26:24 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/21 23:32:44 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	swap(t_env *node1, t_env *node2)
{
	char	*tmp_env;
	char	*tmp_val;

	tmp_env = node1->env;
	tmp_val = node1->value;
	node1->env = node2->env;
	node1->value = node2->value;
	node2->env = tmp_env;
	node2->value = tmp_val;
}

void	print_env(t_env *e)
{
	while (e)
	{
		if (!e->value)
			printf("declare -x %s\n", e->env);
		else
			printf("declare -x %s=\"%s\"\n", e->env, e->value);
		e = e->next;
	}
}

void	sorted_env(t_env *head)
{
	int		swp;
	t_env	*cur;

	swp = 1;
	if (!head || !head->next)
		return ;
	while (swp)
	{
		swp = 0; /* If swapped is still 0, it means no swaps were made during the inner loop,
		indicating that the linked list is already sorted. In this case, the outer loop terminates, and the sorting process is complete.*/
		cur = head;
		while (cur->next)
		{
			if (ft_strcmp(cur->env, cur->next->env) > 0)
			{
				swap(cur, cur->next);
				swp = 1;
			}
			cur = cur->next;
		}
	}
	cur = head;
	print_env(cur);
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
		sorted_env(g_var.list);
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
