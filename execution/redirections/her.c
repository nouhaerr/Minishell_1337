/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:46:12 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/12 16:24:44 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_expansion_for_heredoc2(char *input, int i, t_env *my_env, char **str)
{
	int		len;
	char	*env;
	char	*str_env;

	
	len = token_word(input, i + 1, -1);
	env = ft_substr(input, i + 1, len);
	if (len != 0)
	{
		// printf("imhier\n");
		// sleep (3);
		env = ft_substr(input, i + 1, len);
		str_env = check_env(env, my_env);
		*str = ft_strjoin(*str, str_env);
		free(env);
	}
	return (i + len);
}

int	env_expansion_for_heredoc(char *input, int i, t_env *my_env, char **str)
{
	char	*itoa;
	char	*str_env;

	if (input[i + 1] == '?')
	{
		itoa = ft_itoa(glb_var.exit_status);
		str_env = ft_strdup(itoa);
		*str = ft_strjoin(*str, str_env);
		free(itoa);
		i++;
	}
	else
		i = env_expansion_for_heredoc2(input, i, my_env, str);
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

char	*her(t_data2 *heredoc, t_env *my_env)
{
	char	*value;
	char	*input;
	char	*str;
	int		i;
	int		len;
	
	str = NULL;
	while (heredoc != NULL)
	{
		value = heredoc -> value;
		input = readline("> ");
		i = 0;
		if (ft_strcmp(input, value) == 0)
			heredoc = heredoc -> next;
		else if (heredoc != NULL && heredoc -> next == NULL)
		{
			if (heredoc -> type == expand)
			{
				while (input[i])
				{
					if (input[i] == '$')
						i = env_expansion_for_heredoc(input, i, my_env, &str);
					else
					{
						len = my_word(input, i);
						str = ft_strjoin(str, ft_substr(input, i, len));
						i += len;
					}
				}
				str = ft_strjoin(str, ft_strdup("\n"));
			}
			else if (heredoc -> type == not_expand)
				str = ft_strjoin(str, ft_strjoin(input, ft_strdup("\n")));
		}
	}
	return (str);
}
