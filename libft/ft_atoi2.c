/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 08:34:00 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/24 14:38:02 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi2(const char *str)
{
	unsigned long long	nbr;
	int					signe;
	int					i;

	i = 0;
	nbr = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (signe > 0 && nbr == 9223372036854775807)
		exit(255);
	if (signe < 0 && nbr == 9223372036854775807)
		exit(1);
	if ((signe > 0 && nbr > 9223372036854775807)
	|| (signe < 0 && nbr > 9223372036854775807))
	{
		printf("minishell: exit: %s: numeric argument required\n", str);
		exit(255);
	}
	return (nbr * signe);
}
