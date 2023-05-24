/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 06:25:08 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/24 20:34:27 by nerrakeb         ###   ########.fr       */
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
	if (res == 2)
		exit(255);
	else if (res == 3)
		exit (1);
	if (res < 0)
		exit(256 - ((res * -1) % 256));
	exit(res % 256);
}

void	sh_exit(t_parser *tmp)
{
	int	s;
	t_parser *ex;

	ex = tmp;
	printf("exit\n");
	if (ex->args)
	{
		if (check_ex_av(ex->args->value))
			av_not_num(ex->args->value);
		// else if (ex->args->next && !check_ex_av(ex->args->value))
		// {
		// 	printf("minishell: exit: too many arguments\n");
		// 	s = ft_atoi(ex->args->value);
		// 	glb_var.exit_status = 1;
		// 	return ;
		// }
		else if (ex->args->next || (ex->args->next && !check_ex_av(ex->args->value)))
		{
			if (ex->args->next->value && !check_ex_av(ex->args->value))
			{
				s = ft_atoi2(ex->args->value);
				if (s == 2)
				{
					printf("minishell: exit: too many arguments\n");
					glb_var.exit_status = 1;
				}
				else if (s == 3)
					exit (1);
			}
			else if (ex->args->next->value)
			{
				printf("minishell: exit: too many arguments\n");
				glb_var.exit_status = 1;
				return ;
			}
		}
		else if (!check_ex_av(ex->args->value)) //we have one arg numeric we check if it's positive or negative
			ex_stat(ex->args->value);
	}
	else
		exit(glb_var.exit_status);
}
