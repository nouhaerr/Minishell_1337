/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:32:33 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 10:37:38 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct t_env
{
	char			*env;
	char			*value;
	struct t_env	*next;
}	t_env;

// hier im gonna have functions that is related to env.

t_env	*save_my_env(char **env);
t_env	*ft_lstnew_env(char *env, char *value);
void	ft_lstaddback_env(t_env **lst, t_env *new);
char	*check_env(char *env, t_env *my_envs);

#endif