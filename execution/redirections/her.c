/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:46:12 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/25 15:50:13 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_expansion_for_my_heredoc2(char *input, int i, char **str)
{
	int		len;
	char	*env;
	char	*str_env;

	len = token_word(input, i + 1, -1);
	if (len != 0)
	{
		env = ft_substr(input, i + 1, len);
		str_env = check_env(env, g_var.list);
		*str = ft_strjoin(*str, str_env);
		free(env);
	}
	return (i + len);
}

int	env_expansion_for_my_heredoc(char *input, int i, int index, char **str)
{
	char	*itoa;
	char	*str_env;

	if (input[i + 1] == '?')
	{
		itoa = ft_itoa(g_var.exit_status);
		if (index == 0)
			str_env = ft_strdup(itoa);
		else
			str_env = ft_strdup ("0");
		*str = ft_strjoin(*str, str_env);
		free(itoa);
		i++;
	}
	else
		i = env_expansion_for_my_heredoc2(input, i,  str);
	return (i + 1);
}

int	my_word(char *input, int start)
{
	int	j;

	j = 0;
	while (input[start] && ft_strchr("$|><", input[start]) == NULL)
	{
		j++;
		start++;
	}
	return (j);
}

void	expansion_my_heredoc(char *input, int i, char **str, int index)
{
	int		len ;
	char	*s1;

	len = 0;
	while (input[i])
	{
		if (input[i] == '$')
			i = env_expansion_for_my_heredoc(input, i, index, str);
		else
		{
			len = my_word(input, i);
			s1 = ft_substr(input, i, len);
			*str = ft_strjoin(*str, s1);
			i += len;
		}
	}
	*str = ft_strjoin(*str, ft_strdup("\n"));
	free(input);
}

void	her(t_data2 *my_heredoc, int index, int *pipefd)
{
	char	*input;
	char	*str;
	t_data2	*h_next;
	int		i;

	str = NULL;
	close(pipefd[0]);
	input = readline("> ");
	check_my_heredoc(my_heredoc -> next, &h_next);
	while (input != NULL && ft_strcmp(input, my_heredoc -> value))
	{
		i = 0;
		if (my_heredoc != NULL && h_next == NULL)
		{
			if (my_heredoc -> type == expand)
				expansion_my_heredoc(input, i, &str, index);
			else if (my_heredoc -> type == not_expand)
				str = ft_strjoin(str, ft_strjoin(input, ft_strdup("\n")));
		}
		else
			free(input);
		input = readline("> ");
	}
	write (pipefd[1], str, ft_strlen(str));
	close(pipefd[1]);
}
