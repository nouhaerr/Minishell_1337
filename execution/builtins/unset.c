/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:11:55 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/24 18:47:19 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_isalpha(av[i]) || !ft_isdigit(av[i]) || av[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	ft_list_remove_if(t_env **head, void *data, int *(cmp)())
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
	ft_list_remove_if(&tmp->env, data, cmp);
}

void	sh_unset(t_env *myenv, char **arg)
{
	int		i;
	t_env	*tmp;

	i = 1;
	tmp = myenv;
	if (arg[1][0] == '-' && arg[1][1])
		{
			printf("minishell: unset: %s: invalid option\n", arg[1]);
			printf("unset: usage: unset [-f] [-v] [name ...]\n");
			glb_var.exit_status = 2;
			return ;
		}
	while (arg[i])
	{
		if (unset_arg(arg[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", arg[i]);
			glb_var.exit_status = 1;
			return ;
		}
		while (tmp)
		{
			if (ft_strncmp(tmp->env, arg[i], ft_strlen(arg[i])) == 0)
				ft_list_remove_if(&tmp, arg[i], ft_strcmp);
			tmp = tmp->next;
		}
		i++;
	}
	glb_var.exit_status = 0;
}
