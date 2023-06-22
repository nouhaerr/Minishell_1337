/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:53:09 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/21 22:02:00 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		new = (char *)malloc(1);
		if (!new)
			return (0);
		new[0] = '\0';
		return (new);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (0);
	while (i < len)
	{
        printf ("->imhier\n");
		new[i++] = s[start++];
        if (s[start] == 9)
        {
            printf("imhier\n");
            new[i++] = '\0';
        }
    }
	new[i] = '\0';
	return (new);
}