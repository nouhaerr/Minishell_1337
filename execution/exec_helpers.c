/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:25:27 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/26 23:18:54 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_err(char *s, char *cmd, char *s2)
{
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(s2, STDERR_FILENO);
	exit(g_var.exit_status);
}

int	ft_check_fork(int p)
{
	if (p == -1)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

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

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*ft_add_arr(t_env *en, int en_len, int val_len)
{
	int		j;
	int		l;
	char	*add;

	en_len = ft_strlen(en->env);
	val_len = ft_strlen(en->value);
	add = (char *)malloc((en_len + val_len + 2) * sizeof(char *));
	if (!add)
		return (NULL);
	j = 0;
	while (j < en_len)
	{
		add[j] = en->env[j];
		j++;
	}
	add[j++] = '=';
	l = 0;
	while (l < val_len)
	{
		add[j++] = en->value[l];
		l++;
	}
	add[j] = '\0';
	return (add);
}

char	**create_env_arr(int size)
{
	char	**arr;
	char	*add;
	t_env	*en;
	int		en_lenght;
	int		val_lenght;
	int		i;

	en = g_var.list;
	i = 0;
	en_lenght = 0;
	val_lenght = 0;
	arr = (char **)malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (printf("minishell: Memory allocation failed\n"), NULL);
	while (en)
	{
		add = ft_add_arr(en, en_lenght, val_lenght);
		if (!add)
			return (printf("minishell: Memory allocation failed\n"),
				ft_free(arr), free(add), NULL);
		arr[i] = add;
		en = en->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
