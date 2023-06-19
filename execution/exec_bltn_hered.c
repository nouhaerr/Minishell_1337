/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bltn_hered.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/19 19:38:51 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void  exec_heredoc(t_parser *parser, t_data **my_heredoc)
{
	//char	str[BUFFER_SIZE];
	int		pid;
	int		status;
	int		pipefd[2];
	
	(void)my_heredoc;
	while (parser)
	{
		if (parser->inf_her != NULL)
		{
			pipe(pipefd);
			pid =  fork();
			if (pid == 0)
			{
				// check_signal_heredoc();
				her(parser -> inf_her, g_var.list, pipefd);
				exit (0);
			}
			waitpid(pid, &status, 0);
			if (status == 256)
				g_var.exit_status = 1;
			parser->fd[0] = pipefd[0];
		}
		parser = parser->next;
	}
	close(pipefd[1]);
}

void	run_builtin(t_parser *parser)
{
	char	*cmd2;

	cmd2 = ft_strdup(parser->cmd);
	ft_tolower2(cmd2);
	if (!ft_strcmp(cmd2, "pwd"))
		sh_pwd();
	else if (!ft_strcmp(cmd2, "echo"))
		sh_echo(&parser);
	else if (!ft_strcmp(parser->cmd, "exit"))
		sh_exit(parser);
	else if (!ft_strcmp(cmd2, "env"))
		sh_env();
	else if (!ft_strcmp(parser->cmd, "unset"))
		sh_unset(parser->args);
	else if (!ft_strcmp(cmd2, "cd"))
		sh_cd(parser);
	else if (!ft_strcmp(parser->cmd, "export"))
		sh_export(parser);
	free(cmd2);
}

void	builtin_executor(t_parser *node, t_pipe pip, char *msg)
{
	int	*fl;

	fl = dup_and_exec(node, pip, msg);
	if (!fl)
	{
		g_var.exit_status = 1;
		return ;
	}
	run_builtin(node);
	update_fd(g_var.fd_prog);
	free(fl);
}
