/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:55:05 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/18 19:17:05 by nerrakeb         ###   ########.fr       */
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

void    signal_check(void)
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
void	check_signal_heredoc(void)
{
	signal(SIGINT, signal_heredoc);
}