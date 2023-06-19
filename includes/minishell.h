/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:53:18 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/19 14:22:49 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../includes/lexer.h"
# include "../includes/parser.h"
# include "../includes/execution.h"
# include "../includes/env.h"
# include "../execution/builtins/builtins.h"
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "../includes/execution.h"
# include <signal.h>
# include <termios.h>

#define BUFFER_SIZE 1024
typedef struct s_glb
{
	t_env	*list;
	int		exit_status;
	int		signal_heredoc;
	bool	parent_process;
	int		*fd_prog;
}	t_glb;

t_glb	g_var;

// thsi one must stau hier since they dont know the prototype of this function
//gotta add this cause in the library i downloaded they didnt have the prototype
void	rl_replace_line(const char *text, int clear_undo);
size_t	env_list_size(t_env *env);
void	signal_check(void);
void	check_signal_heredoc(void);

#endif