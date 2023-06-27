/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:48:48 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/27 15:08:40 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_add_arr(t_env *en, int en_len, int val_len)
{
	int		j;
	int		l;
	char	*add;

	en_len = ft_strlen(en->env);
	val_len = ft_strlen(en->value);
	add = (char *)malloc((en_len + val_len + 2) * sizeof(char *));
	if (!add)
		return (NULL);
	j = 0;
	while (j < en_len)
	{
		add[j] = en->env[j];
		j++;
	}
	add[j++] = '=';
	l = 0;
	while (l < val_len)
	{
		add[j++] = en->value[l];
		l++;
	}
	add[j] = '\0';
	return (add);
}

void	add_to_under_score(t_parser *parser)
{
	char	*str;
	t_env	*node;

	while (parser -> next)
		parser = parser -> next;
	if (parser -> args == NULL)
		str = parser -> cmd;
	else
	{
		while (parser -> args -> next)
			parser -> args = parser -> args -> next;
		str = parser -> args -> value;
	}
	node = ft_getenv(g_var.list, "_");
	if (node != NULL)
	{
		free(node -> value);
		node -> value = ft_strdup(str);
	}
}

char	**create_env_arr(int size)
{
	t_helper	*h;

	h = malloc(sizeof(t_helper));
	h ->en = g_var.list;
	h ->i = 0;
	h ->en_lenght = 0;
	h ->val_lenght = 0;
	h ->arr = (char **)malloc((size + 1) * sizeof(char *));
	if (!(h-> arr))
		return (printf("minishell: Memory allocation failed\n"), NULL);
	while (h -> en)
	{
		h -> add = ft_add_arr(h -> en, h -> en_lenght, h -> val_lenght);
		if (!(h -> add))
			return (printf("minishell: Memory allocation failed\n"),
				ft_free(h -> arr), free(h ->add), NULL);
		h -> arr[h -> i] = h -> add;
		h -> en = h -> en->next;
		h -> i++;
	}
	h -> arr[h -> i] = NULL;
	return (h ->arr);
}
