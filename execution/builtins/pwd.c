/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 06:15:22 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/26 16:16:05 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_env(t_env *head, char *s)
{
	int		l;
	int		len;
	t_env	*node;

	len = ft_strlen(s);
	node = head;
	while (node)
	{
		l = ft_strlen(node->env);
		if (len == l && !ft_strncmp(node->env, s, len))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	sh_pwd(void)
{
	char	buf[4096];
	t_env	*s;

	if (!getcwd(buf, 4096))
	{
		if (env_search(g_var.list, "PWD"))
		{
			s = find_env(g_var.list, "PWD");
			printf("%s\n", s->value);
		}
	}
	else
		printf("%s\n", buf);
}
