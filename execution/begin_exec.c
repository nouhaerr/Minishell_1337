/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 05:37:14 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/15 10:24:18 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**real_path(char **env)
{
	char	**p;
	t_env	*cur;
	int		i;

	i = 0;
	cur = glb_var.list;
	while (cur)
	{
		if (!ft_strncmp(cur->env, "PATH=", 5))
		{
			p = ft_split(cur->env + 5, ':');
			return (p);
		}
		cur = cur->next;
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
