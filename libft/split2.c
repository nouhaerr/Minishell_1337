/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:23 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/26 13:38:46 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	counter(char const *s, int a)
// {
// 	int	i;
// 	int	j;
// 	int	a;

// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
		
// 	}
// 	return (j);
// }

int	word(char const *s, int start, int i, int a)
{
	int	j;

	j = 0;
	(void)a;
	(void)i;
	while (s[start] != ' ' && s[start])
	{
		j++;
		start++;
	}
	printf("->%d==", i);
	if (i + 1 == a)
	{
		if (s[start] == ' ' && s[start + 1] == ' ')
			start++;
		while (s[start])
		{
			start++;
			j++;
		}
	}
	printf("[%c]== %d\n", s[start], start);
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

char	**split2(char const *s, char c, int a, int b)
{
	int		i;
	int		j;
	char	**p;

	if (s == NULL)
		return (NULL);
	printf("->>> [%s=====%d ==%d]\n", s, a, b);
	sleep (1);
	p = malloc(sizeof(char *) * (a + 1));
	i = -1;
	j = 0;
	if (!p)
		return (NULL);
	while (++i < a)
	{
		while (s[j] == c && s[j + 1] != c)
			j++;
		if (i == 0 || b != 1)
			p[i] = ft_substr2(s, j, word(s, j, i, a));
		else
			p[i] = ft_strdup ("\0");
		if (!p[i])
		{
			free2(p, i);
			return (NULL);
		}
		j += word(s, j, i, a);
	}
	p[i] = 0;
	return (p);
}
