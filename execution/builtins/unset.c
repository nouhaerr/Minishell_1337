/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:11:55 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/01 06:38:22 by nerrakeb         ###   ########.fr       */
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
	int 	len;

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

void	sh_unset(t_parser *arg)
{
	int		i;
	t_parser	*cur;

	i = 0;
	cur = arg;	
	if (!cur->args)
		return ;
	if (cur->args->value[i] == '-' && cur->args->value[i + 1])
	{
		unset_error(cur->args);
		return ;
	}
	while (cur->args)
	{
		if (!unset_arg(cur->args->value) || ft_isdigit(cur->args->value[0]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cur->args->value);
			glb_var.exit_status = 1;
		}
		if (env_search(glb_var.list, cur->args->value))
			ft_list_remove_if(&glb_var.list, cur->args->value);
		cur->args = cur->args->next;
	}
	if (glb_var.exit_status == 1)
		glb_var.exit_status = 1;
	else
		glb_var.exit_status = 0;
}
