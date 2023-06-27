/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:00:11 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/27 17:07:50 by nerrakeb         ###   ########.fr       */
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

void	duplicate_env(t_env *head, t_env **tmp)
{
	t_env	*h;

	h = head;
	while (h)
	{
		ft_lstaddback_env(tmp, ft_lstnew_env(ft_strdup(h ->env),
				ft_strdup(h ->value)));
		h = h -> next;
	}
}

void	sorted_env(t_env *head)
{
	int		swp;
	t_env	*cur;
	t_env	*tmp;

	if (!head || !head->next)
		return ;
	swp = 1;
	tmp = NULL;
	duplicate_env(head, &tmp);
	while (swp)
	{
		swp = 0;
		cur = tmp;
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
	cur = tmp;
	print_env(cur);
}
