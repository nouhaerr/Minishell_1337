/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:37:58 by hobenaba          #+#    #+#             */
/*   Updated: 2023/02/03 19:16:22 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_mycopy_gnl(char *into, char *from)
{
	int	j;

	j = 0;
	if (from == NULL)
		return (NULL);
	while (from[j])
	{
		into[j] = from[j];
		j++;
	}
	return (into);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*p;

	if (s1 == NULL)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_mycopy_gnl(p, s1);
	ft_mycopy_gnl(p + ft_strlen(s1), s2);
	p[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (p);
}

int	ft_strstop(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n' && s[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}
