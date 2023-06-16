/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 02:44:45 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/16 17:55:45 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			j = s1[i] - s2[i];
			free(s1);
			return (j);
		}
		i++;
	}
	free(s1);
	return (0);
}
