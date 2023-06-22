/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 05:37:14 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/22 18:06:33 by hobenaba         ###   ########.fr       */
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
			str = ft_strjoin2(str, "	");
		str = ft_strjoin2(str, cur -> value);
		str = ft_strjoin2(str, " ");
		cur = cur -> next;
	}
	s1 = split2(str, ' ');
	int i;

	i = 0;
	while (s1[i])
	{
		printf("s1[i] : %s\n",s1[i]);
		i++;
	}
	free(str);
	return (s1);
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

char	*get_path(char *cmd, t_parser *parser)
{
	char	*path;
	char	*cmd_file;
	char	**full_path;
	int		i;

	full_path = real_path();
	if (!full_path && parser -> my_cmd == 0)
		ft_err("minishell: ", cmd, ": command not found");
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
