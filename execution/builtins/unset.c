/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:11:55 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/25 15:14:43 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!(ft_isalpha(av[i]) || ft_isdigit(av[i]) || av[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_list_remove_if(t_env **head, void *data, int (*cmp)())
{
	t_env	*tmp;

	tmp = *head;
	if (!(*head) || !head)
		return ;
	if (cmp(tmp->env, data) == 0)
	{
		*head = tmp->next;
		free(tmp->env);
		free(tmp->value);
		free(tmp);
		ft_list_remove_if(head, data, cmp);
	}
	tmp = *head;
	ft_list_remove_if(&tmp, data, cmp);
}

void	sh_unset(t_data *arg)
{
	int		i;
	t_env	*tmp;
	t_data	*cur;

	i = 0;
	tmp = glb_var.list;
	cur = arg;
	if (cur->value[i] == '-' && cur->value[i + 1])
		{
			printf("minishell: unset: %s: invalid option\n", arg->value);
			printf("unset: usage: unset [-f] [-v] [name ...]\n");
			glb_var.exit_status = 2;
			return ;
		}
	while (cur)
	{
		if (!unset_arg(cur->value) || ft_isdigit(cur->value[0]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cur->value);
			glb_var.exit_status = 1;
			return ;
		}
		while (tmp)
		{
			if (ft_strncmp(tmp->env, cur->value, ft_strlen(cur->value)) == 0)
				ft_list_remove_if(&tmp, cur->value, ft_strcmp);
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	glb_var.exit_status = 0;
}
