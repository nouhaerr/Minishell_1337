/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:18:14 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/09 14:53:57 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_av(t_data *av, int newline)
{
	int	i;
	t_data	*tmp;

	i = 0;
	tmp = av;
	while (tmp)
	{
		printf("%s", tmp->value);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
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
	return (0);
}

void	check_n(t_data *arg)
{
	int	i;
	t_data *tmp;

	i = 0;
	tmp = arg;
	if (non_n_carcacters(tmp->value + 1)) //av[i]+1 to skip '-' character and that means that all characters following the hyphen in the current argument are not 'n'
	{
		print_av(tmp, 1);
		return ;//ending the execution of the function.
	}
	while (tmp && tmp->value[i] == '-' && !non_n_carcacters(tmp->value + 1))
		tmp = tmp->next; //move to the next arg
	if (!tmp) // akhir arg is NULL yaeni endna just -nn f gaa3 args w sf ankhrjo mn function or haja akhra a part duk -n
		return ; //ending the execution of the function without doing anything cuz we have all args = -n.
	print_av(tmp, 0); //kayna haja akhra a part duk -n we print it without newline
}

void	sh_echo(t_parser **echo)
{
	int	i;
	t_parser *tmp;
	
	i = 0;
	tmp = *echo;
	glb_var.exit_status = 0;
	if (!tmp->args) // check arg is null
		printf("\n");
	else if (tmp->args->value[0] == '-')
		check_n(tmp->args);
	else
		print_av(tmp->args, 1);
}
