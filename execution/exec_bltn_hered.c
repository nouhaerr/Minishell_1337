/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bltn_hered.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/25 15:00:03 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_my_heredoc(t_data2 *inf_her, t_data2 **my_heredoc)
{
	while (inf_her)
	{
		if (inf_her -> type != infile)
		{
			*my_heredoc = inf_her;
			break ;
		}
		inf_her = inf_her -> next;
	}
}

void	exec_heredoc(t_parser *parser)
{
	t_data2		*my_heredoc;
	t_parser	*p;
	t_data2		*inf_her;

	p = parser;
	inf_her = p -> inf_her;
	while (p)
	{
		while (inf_her)
		{
			my_heredoc = NULL;
			check_my_heredoc(inf_her, &my_heredoc);
			if (my_heredoc != NULL)
				write_her(my_heredoc, p);
			if (my_heredoc != NULL)
				inf_her = my_heredoc -> next;
			else
				inf_her = my_heredoc;
		}
		p = p->next;
	}
}

void	write_her(t_data2 *my_heredoc, t_parser *p)
{
	int	pipefd[2];
	int	pid;
	int	status;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		//check_signal_heredoc();
		her(my_heredoc, p -> index, pipefd);
		exit (0);
	}
	waitpid(pid, &status, 0);
	g_var.exit_status = WEXITSTATUS(status);
	close(pipefd[1]);
	p->fd[0] = pipefd[0];
	printf("%d\t%d\n", p->fd[0], p -> fd[1]);
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
		sh_unset(parser->args_exec);
	else if (!ft_strcmp(cmd2, "cd"))
		sh_cd(parser);
	else if (!ft_strcmp(parser->cmd, "export"))
		sh_export(parser);
	free(cmd2);
}

void	builtin_executor(t_parser *node, t_pipe pip, char *msg)
{
	int	*fl;

	fl = dup_fd(node, pip, msg);
	if (!fl)
	{
		g_var.exit_status = 1;
		return ;
	}
	run_builtin(node);
	update_fd(g_var.fd_prog);
	free(fl);
}
