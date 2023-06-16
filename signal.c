/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:55:05 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/16 21:28:48 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	signal_handler(int signal)
{
	(void)signal;
	//printf("->>>>>>> imhier\n");
	rl_on_new_line();
	rl_replace_line(" ", 0);
	rl_redisplay();
}

void    signal_check()
{
	sig_t i;
	
	i = signal(SIGINT, signal_handler);
}
