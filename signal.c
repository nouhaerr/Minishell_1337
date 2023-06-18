/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:55:05 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/18 11:51:59 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_var.exit_status = 1;
}

void    signal_check()
{
	//remove_ctrl();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
void	signal_heredoc(int signal)
{
	(void)signal;
	
	//write (1, "\n>", 2);
	g_var.exit_status = 1;
	g_var.her_ctrlc = 1;
}
void	check_signal_heredoc()
{
	signal(SIGINT, signal_heredoc);
}