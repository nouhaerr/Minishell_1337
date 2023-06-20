/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:46:12 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/20 16:34:15 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_expansion_for_my_heredoc2(char *input, int i, t_env *my_env, char **str)
{
	int		len;
	char	*env;
	char	*str_env;

	len = token_word(input, i + 1, -1);
	if (len != 0)
	{
		env = ft_substr(input, i + 1, len);
		str_env = check_env(env, my_env);
		*str = ft_strjoin(*str, str_env);
		free(env);
	}
	return (i + len);
}

int	env_expansion_for_my_heredoc(char *input, int i, t_env *my_env, char **str)
{
	char	*itoa;
	char	*str_env;

	if (input[i + 1] == '?')
	{
		itoa = ft_itoa(g_var.exit_status);
		str_env = ft_strdup(itoa);
		*str = ft_strjoin(*str, str_env);
		free(itoa);
		i++;
	}
	else
		i = env_expansion_for_my_heredoc2(input, i, my_env, str);
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

void	expansion_my_heredoc(char *input, int i, char **str, t_env *my_env)
{
	int	len ;
	char *s1;

	len = 0;
	while (input[i])
	{
		if (input[i] == '$')
			i = env_expansion_for_my_heredoc(input, i, my_env, str);
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

void	her(t_data2 *my_heredoc, t_env *my_env, int *pipefd)
{
	char	*input;
	char	*str;
	int		i;

	str = NULL;
	(void)pipefd;
	input = readline("> ");
	while (input != NULL && ft_strcmp(input, my_heredoc -> value))
	{
		i = 0;
		if (my_heredoc != NULL && my_heredoc -> next == NULL)
		{
			if (my_heredoc -> type == expand)
				expansion_my_heredoc(input, i, &str, my_env);
			else if (my_heredoc -> type == not_expand)
				str = ft_strjoin(str, ft_strjoin(input, ft_strdup("\n")));
		}
		else
			free(input);
		input = readline("> ");
	}
	close(pipefd[0]);
	write (pipefd[1], str, ft_strlen(str) + 1);
	close(pipefd[1]);
}
