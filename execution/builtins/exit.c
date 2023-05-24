/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:25:08 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/24 10:04:52 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_ex_av(char *av)
{
	int	i;

	i = 0;
	if (!(*av))
		return (1);
	if (*av == '-' || *av == '+')
		av++;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	av_not_num(char *arg)
{
	printf("minishell: exit: %s: numeric argument required\n", arg);
	exit(255);
}

static void	ex_stat(char *arg)
{
	int	res;

	res = ft_atoi2(arg);
	if (res < 0)
		exit(256 - ((res * -1) % 256));
	exit(res % 256);
}

void	sh_exit(char **argv)
{
	int	s;

	printf("exit\n");
	if (argv[1])
	{
		if (check_ex_av(argv[1]))
			av_not_num(argv[1]);
		else if (argv[2] && !check_ex_av(argv[1]))
			s = ft_atoi(argv[1]);
		else if (argv[2] || (argv[2] && !check_ex_av(argv[1])))
		{
			printf("minishell: exit: too many arguments\n");
			glb_var.exit_status = 1;
			return ;
		}
		else if (!check_ex_av(argv[1])) //we have one arg numeric we check if it's positive or negative
			ex_stat(argv[1]);
	}
	else
		exit(glb_var.exit_status);
}
