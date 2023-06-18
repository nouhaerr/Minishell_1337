/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bltn_hered.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:45:32 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/18 15:34:29 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_heredoc(t_parser *parser, t_data **my_heredoc)
{
	char	*str;
	// int		fd;
	// int		status;
	//int		pipefd[2];
	
	(void)my_heredoc;
	str = NULL;
	//check_signal_heredoc();
	while (parser)
	{
		g_var.her_ctrlc = 0;
		if (parser -> heredoc != NULL)
		{	
			//fd =  fork();
			// if (fd == 0)
				her(parser -> heredoc, g_var.list);
			//waitpid(fd, &status, 0);
		ft_lstaddback2(my_heredoc, ft_lstnew2(str));
		free (str);
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
