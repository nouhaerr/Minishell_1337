/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:38:39 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/14 12:19:33 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstnew_env(char *env, char *value)
{
	t_env	*p;

	p = malloc(sizeof (t_env));
	if (!p)
		return (NULL);
	p -> value = value;
	p -> env = env;
	p -> next = NULL;
	return (p);
}

void	ft_lstaddback_env(t_env **lst, t_env *new)
{
	t_env	*p;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	if (!p)
		return ;
	while (p-> next)
		p = p -> next;
	p -> next = new;
}

t_env	*save_my_env(char **env)
{
	t_env	*my_env;
	int		i;
	int		start;
	int		len;

	i = 0;
	my_env = NULL;
	while (env[i])
	{
		start = 0;
		len = 0;
		while (env[i][len])
		{
			if (env[i][len] == '=')
			{
				start = len + 1;
				break ;
			}
			len++;
		}
		if (ft_strcmp(ft_substr(env[i], 0, len), "OLDPWD"))
			ft_lstaddback_env(&my_env, ft_lstnew_env(ft_substr(env[i], 0, len), ft_substr(env[i], start, ft_strlen(env[i]) - 1)));
		i++;
	}
	return (my_env);
}

char	*check_env(char *env, t_env *my_envs)
{
	t_env	*e;

	e = my_envs;
	while (e)
	{
		if (!ft_strcmp(env, e->env))
			return (ft_strdup(e -> value));
		e = e -> next;
	}
	return (NULL);
}

size_t	env_list_size(t_env *env)
{
	size_t	len;

	len = 0;
	if (!env)
		return (0);
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}
