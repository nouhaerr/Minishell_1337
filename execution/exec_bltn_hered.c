/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bltn_hered.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/19 15:50:37 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_heredoc(t_parser *parser, t_data **my_heredoc)
{
	char	str[BUFFER_SIZE];
	int		fd;
	int		status;
	int		pipefd[2];

	*my_heredoc = NULL;
	while (parser)
	{
		pipe(pipefd);
		if (parser -> heredoc != NULL)
		{	
			g_var.signal_heredoc = 1;
			fd =  fork();
			if (fd == 0)
			{
				check_signal_heredoc();
				her(parser -> heredoc, g_var.list, pipefd);
				exit (0);
			}
			waitpid(fd, &status, 0);
			if (status == 256)
				g_var.exit_status = 1;
			read(pipefd[0], str, BUFFER_SIZE);
			printf("%s\n", str);
			ft_lstaddback2(my_heredoc, ft_lstnew2(str)); //why does it stand here
			//printf("hier : %s\n , address %p\n", str, *my_heredoc);
			//sleep (1);
		}
		parser = parser -> next;
	}
	while (*my_heredoc)
	{
		printf("->>>> %s\n", (*my_heredoc) -> value);
		*my_heredoc = (*my_heredoc) -> next;
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
