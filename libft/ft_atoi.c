/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:00:55 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/25 14:03:38 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ff_atoi(const char *str, int signe, long res)
// {
	
// }

long	ft_atoi(const char *str)
{
	int				signe;
	unsigned long	res;

	signe = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (signe > 0 && res == 9223372036854775807)
		return (2);
	if (signe < 0 && res == 9223372036854775807)
		return (3);
	if ((signe > 0 && res > 9223372036854775807)
	|| (signe < 0 && res > 9223372036854775807))
	{
		printf("minishell: exit: %s: numeric argument required\n", str);
		exit(255);
	}
	return (signe * res);
}
