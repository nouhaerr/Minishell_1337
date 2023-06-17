/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:19:54 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/17 20:12:00 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*args(t_data *arg)
// {
// 	char	**args;
// 	char	*add;
// 	int		size;
// 	int		i;

// 	i = 0;
// 	args = (char **)malloc((size + 1) * sizeof(char *));
// 	if (!args)
// 		return (printf("minishell: Memory allocation failed\n"));
// 	while (arg)
// 	{
// 		args[i] = ft_strjoin(arg->value, " ");
// 		if (!args[i])
// 			return (printf("minishell: Memory allocation failed\n"), ft_free(args), free(add), NULL);
// 		arg = arg->next;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

// char	**cmd_table(t_parser *cmds)
// {
// 	char	**arr;
// 	char	*add;
// 	int		size;
// 	int		i;

// 	i = 0;
// 	size = ft_lstsize_parse(cmds);
// 	arr = (char **)malloc((size + 1) * sizeof(char *));
// 	if (!arr)
// 		return (printf("minishell: Memory allocation failed\n"));
// 	while (cmds)
// 	{
// 		add = ft_strjoin(cmds->cmd, " ");
// 		if (!add)
// 			return (printf("minishell: Memory allocation failed\n"), ft_free(arr), NULL);
// 		arr[i]= ft_strjoin(add, cmds->args);
// 		if (!arr[i])
// 			return (printf("minishell: Memory allocation failed\n"), ft_free(arr), free(add), NULL);
// 		free(add);
// 		cmds = cmds->next;
// 		i++;
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }

void	switch_pipe(t_pipe *pip, int i, int fd_pip[2][2])
{
	if (i % 2 == 0)
	{
		pip->rd_end = fd_pip[0];
		pip->wr_end = fd_pip[1];
	}
	else
	{
		pip->rd_end = fd_pip[1];
		pip->wr_end = fd_pip[0];
	}
}

void	open_pipes(t_pipe pip, int index)
{
	if (index == 0)
	{
		pipe(pip.rd_end);
		pipe(pip.wr_end);
	}
	else
		pipe(pip.wr_end);
}

int	multiple_pipes(t_parser *node)
{
	t_pipe		pip;
	t_parser	*cur;
	pid_t		pid;
	int			fd_pip[2][2];

	cur = node;
	while (cur)
	{
		switch_pipe(&pip, cur->index, fd_pip);
		open_pipes(pip, cur->index);
		if (cur == node)
			pid = exec_cmd(node, pip, "first");
		else if (cur->next == NULL)
			pid = exec_cmd(node, pip, "last");
		else
			pid = exec_cmd(node, pip, "between");
		close(pip.rd_end[0]);
		close(pip.rd_end[1]);
		cur = cur->next;
	}
	close(pip.wr_end[0]);
	close(pip.wr_end[1]);
	return (pid);
}
