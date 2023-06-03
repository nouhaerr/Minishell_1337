/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 05:37:14 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/01 06:01:51 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_slash(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_err(char *s, char *cmd)
{
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	exit(127);
}

char	**real_path(char **env)
{
	char	**p;
	int		i;

	i = 0;
	while (glb_var.list->env)
	{
		if (!ft_strncmp(glb_var.list->env, "PATH=", 5))
		{
			p = ft_split(glb_var.list->env + 5, ':');
			return (p);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	*path;
	char	*cmd_file;
	char	**full_path;
	int		i;

	full_path = real_path(glb_var.list);
	if (!full_path)
		ft_err("pipex: command not found: ", cmd);
	cmd_file = ft_strjoin("/", cmd);
	i = -1;
	while (full_path[++i])
	{
		path = ft_strjoin(full_path[i], cmd_file);
		if (!access(path, F_OK | X_OK))
			return (ft_free(full_path), free(cmd_file), path);
		free(path);
	}
	ft_free(full_path);
	return (NULL);
}

void	begin_exec(t_parser *parser, char *cmd2)
{
	(void)parser;
	char	*path;

	path = cmd2;
	if (!cmd_slash(cmd2))
		path = get_path(cmd2);
	if (!path)
		ft_err("minishell: command not found: ", cmd2);
	ft_execve(path, cmd2, glb_var.list);
}