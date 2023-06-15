/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:53:18 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/15 09:31:51 by nerrakeb         ###   ########.fr       */
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

typedef struct s_glb
{
	t_env	*list;
	int		exit_status;
	bool	parent_process;
}	t_glb;

t_glb	glb_var;

// thsi one must stau hier since they dont know the prototype of this function

void	rl_replace_line (const char *text, int clear_undo);  // gotta add this cause in the library i downloaded they didnt have the prototype
void	signal_heredoc(int signal, siginfo_t *infos , void *contest);
size_t	env_list_size(t_env *env);

#endif