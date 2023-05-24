/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:18:14 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/23 13:09:05 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_av(char **av, int newline)
{
	int	i;

	i = 0;
	while (av[i])
	{
		printf("%s", av[i++]);
		if (av[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}

int	non_n_carcacters(char *ntr)
{
	if (!(*ntr))
		return (1);
	while (*ntr)
	{
		if (*ntr != 'n')
			return (1);
		ntr++;
	}
	return (0); //all characters are 'n'
}

void	check_n(char **av)
{
	int	i;

	i = 2; // i = 1;
	if (non_n_carcacters(av[i] + 1)) //av[i]+1 to skip '-' character and that means that all characters following the hyphen in the current argument are not 'n'
	{
		print_av(av + i, 1);
		return ;//ending the execution of the function.
	}
	while (av[i] && *av[i] == '-' && !non_n_carcacters(av[i] + 1))
		i++; //move to the next arg
	if (!av[i]) // akhir arg is NULL yaeni endna just -nn f gaa3 args w sf ankhrjo mn function or haja akhra a part duk -n
		return ; //ending the execution of the function without doing anything cuz we have all args = -n.
	print_av(av + i, 0); //kayna haja akhra a part duk -n we print it without newline
}

void	sh_echo(char **argv)
{
	int	i;
	
	i = 0;
	if (!argv[2]) // 1
		printf("\n");
	else if (argv[2][0] == '-') //1
		check_n(argv);
	else
		print_av(&argv[i + 2], 1); // i + 1
}
