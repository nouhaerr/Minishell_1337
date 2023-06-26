/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bltn_hered.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/26 18:23:03 by nerrakeb         ###   ########.fr       */
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
	t_data2		*heredoc_next;
	t_parser	*p;
	t_data2		*v;
	t_data2		*inf_her;

	p = parser;
	while (p)
	{
		inf_her = p -> inf_her;
		while (inf_her)
		{
			my_heredoc = NULL;
			heredoc_next = NULL;
			check_my_heredoc(inf_her, &my_heredoc);
			v = my_heredoc;
			if (my_heredoc != NULL)
				check_my_heredoc(v -> next, &heredoc_next);
			if (heredoc_next != NULL)
				v = heredoc_next;
			if (my_heredoc != NULL)
				write_her(my_heredoc, heredoc_next, p);
			if (my_heredoc != NULL)
				inf_her = heredoc_next;
			else
				inf_her = my_heredoc;
		}
		p = p->next;
	}
}

void	signal_heredoc(int signal)
{
	(void)signal;
	exit(1);
}

void	write_her(t_data2 *my_heredoc, t_data2 *heredoc_next,  t_parser *p)
{
	int	pipefd[2];
	int	pid;
	int	status;

	if (heredoc_next == NULL)
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, signal_heredoc);
		her(my_heredoc, heredoc_next, p -> index, pipefd);
		exit (0);
	}
	waitpid(pid, &status, 0);
	g_var.exit_status = WEXITSTATUS(status);
	if (heredoc_next == NULL)
	{
		close(pipefd[1]);
		p->fd[0] = pipefd[0];
	}
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
