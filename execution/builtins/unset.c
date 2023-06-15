/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:11:55 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/15 07:56:40 by nerrakeb         ###   ########.fr       */
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

void	ft_list_remove_if(t_env **head, void *data)
{
	t_env	*tmp;

	tmp = *head;
	if (!(*head) || !head)
		return ;
	if (ft_strcmp(tmp->env, data) == 0)
	{
		*head = tmp->next;
		free(tmp->env);
		free(tmp->value);
		free(tmp);
		ft_list_remove_if(head, data);
	}
	tmp = *head;
	ft_list_remove_if(&tmp->next, data);
}

int	env_search(t_env *head, char *s)
{
	int		l;
	int		len;

	len = ft_strlen(s);
	while (head)
	{
		l = ft_strlen(head->env);
		if (len == l && !ft_strncmp(head->env, s, len))
			return (1);
		head = head->next;
	}
	return (0);
}

static void	unset_error(t_data *arg)
{
	glb_var.exit_status = 2;
	printf("minishell: unset: %s: invalid option\n", arg->value);
	printf("unset: usage: unset [-f] [-v] [name ...]\n");
}

void	sh_unset(t_data *arg)
{
	int		i;
	t_data	*cur;

	i = 0;
	cur = arg;
	if (!cur)
		return ;
	if (cur->value[i] == '-' && cur->value[i + 1])
	{
		unset_error(cur);
		return ;
	}
	while (cur)
	{
		if (!unset_arg(cur->value) || ft_isdigit(cur->value[0])
			|| cur->value[0] == '\0')
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				cur->value);
			glb_var.exit_status = 1;
		}
		if (env_search(glb_var.list, cur->value))
			ft_list_remove_if(&glb_var.list, cur->value);
		cur = cur->next;
	}
	// ila kane khass n unsetiw bzaaf args w binathom erreur
	if (glb_var.exit_status != 1)
		glb_var.exit_status = 0;
}
