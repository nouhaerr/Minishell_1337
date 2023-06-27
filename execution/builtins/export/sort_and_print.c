/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:00:11 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/27 15:09:45 by nerrakeb         ###   ########.fr       */
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
		swp = 0;
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
