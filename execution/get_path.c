/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 05:37:14 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/25 22:17:38 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**table_cmd(t_parser *node)
{
	char	*str;
	char	**s1;
	t_data	*cur;

	str = NULL;
	cur = node -> args;

	str = ft_strjoin2(node -> cmd, " ");
	while (cur)
	{
		if (cur -> value[0] == '\0')
			str = ft_strjoin2(str, " ");
		else
		{
			str = ft_strjoin2(str, cur -> value);
			str = ft_strjoin2(str, " ");
		}
		cur = cur -> next;
	}
	s1 = split2(str, ' ');
	int i = 0;
	while (s1[i])
	{
		printf("->>>> [%s]\n", s1[i]);
		i++;
	}
	sleep (3);
	free(str);
	return (s1);
}

void	check_dir_notexec(char *path, t_parser *node)
{
	int	dir;

	dir = open(path, O_DIRECTORY);
	if (node->cmd[0] != '\0' && dir != -1)
	{
		close(dir);
		g_var.exit_status = 126;
		ft_err("minishell: ", path, ": is a directory");
	}
	if (node->cmd[0] != '\0' && open(path, O_RDONLY) != -1 && access(path, X_OK))
	{
		perror("minishell");
		exit(126);
	}
}

char	**real_path(void)
{
	char	**p;
	t_env	*cur;
	int		i;

	i = 0;
	cur = g_var.list;
	while (cur)
	{
		if (!ft_strncmp(cur->env, "PATH", 4))
		{
			if (cur->value[0] == ':')
				cur->value = ft_strjoin2(".", cur->value);
			p = ft_split(cur->value, ':');
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

	full_path = real_path();
	if (!full_path)
	{
		g_var.exit_status = 127;
		ft_err("minishell: ", cmd, ": command not found");
	}
	cmd_file = ft_strjoin2("/", cmd);
	i = -1;
	while (full_path[++i])
	{
		path = ft_strjoin2(full_path[i], cmd_file);
		if (!access(path, F_OK | X_OK))
			return (ft_free(full_path), free(cmd_file), path);
		free(path);
	}
	ft_free(full_path);
	return (NULL);
}
