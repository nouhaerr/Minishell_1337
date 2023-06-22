/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:23 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/22 19:48:38 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	counter(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == c)
			j++;
		else if (s[i] != c && s[i + 1] == '\0')
			j++;
		i++;
	}
	return (j);
}

int	word(char const *s, int start, char c)
{
	int	j;

	j = 0;
	while (s[start] != c && s[start])
	{
		j++;
		start++;
	}
	return (j);
}

void	free2(char **p, int i)
{
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
}

char	**split2(char const *s, char c)
{
	int		i;
	int		j;
	char	**p;

	if (s == NULL)
		return (NULL);
	p = malloc(sizeof(char *) * (counter(s, c) + 1));
	i = -1;
	j = 0;
	if (!p)
		return (NULL);
	while (++i < counter(s, c))
	{
		while (s[j] == c)
			j++;
		p[i] = ft_substr2(s, j, word(s, j, c));
		if (!p[i])
		{
			free2(p, i);
			return (NULL);
		}
		j += word(s, j, c);
	}
	p[i] = 0;
	return (p);
}