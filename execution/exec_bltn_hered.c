/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bltn_hered.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/18 19:00:11 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_heredoc(t_parser *parser, t_data **my_heredoc)
{
	void	*str;
	int		fd;
	int		status;
	int		pipefd[2];
	
	(void)my_heredoc;
	str = NULL;
	pipe(pipefd);
	while (parser)
	{
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
			printf("%d\n", pipefd[0]);
			int a = read(0, str, 1);
			printf("i have read %d\n", a);
			printf("->>>> %s\n", str);
			// ft_lstaddback2(my_heredoc, ft_lstnew2(str));
			// free (str);
		}
		parser = parser -> next;
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
