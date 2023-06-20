/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:15:28 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/20 20:50:29 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	other_tokens(t_lexer *lexer, int i, char *input)
{
	int	len;

	len = token_word(input, i, lexer->base);
	if (lexer->base == 0 && input[i] == '#')
		i = ft_strlen(input);
	else
	{
		lexer->str = ft_strjoin(lexer->str, ft_substr(input, i, len));
		i += len;
	}
	return (i);
}

int	partition_tokens(t_lexer *lexer, char *input, int i)
{
	if (lexer->a == 0 && (input[i] == '\'' || input[i] == '\"'))
	{
		lexer->c = input[i];
		lexer->a = 1;
		if (input[i] == '\'')
			lexer->base = 1;
		else
			lexer->base = 2;
		lexer->base2 = lexer->base;
		i++;
	}
	else if (lexer->c == input[i])
	{
		lexer->base = 0;
		lexer->a = 0;
		i++;
	}
	else if (input[i] != '\0')
		i = other_tokens(lexer, i, input);
	return (i);
}

int	token_word(char *input, int start, int base)
{
	if (base < 0)
		return (env_word(input, start));
	else if (base == 0)
		return (normal_word(input, start));
	else
		return (quotes_word(input, start, base));
	return (0);
}

int	token_env2(char *input, int i, t_lexer *lexer)
{
	int		len;
	char	*str_env;
	char	*env;

	len = token_word(input, i + 1, -1);
	if (lexer->her == 0 && (lexer->base == 2 || lexer->base == 0))
	{
		if (len != 0)
		{
			env = ft_substr(input, i + 1, len);
			str_env = check_env(env, g_var.list);
			free(env);
		}
		if (len == 0)
			str_env = ft_strdup("$");
		lexer->str = ft_strjoin(lexer->str, str_env);
	}
	else
	{
		str_env = ft_substr(input, i, len + 1);
		lexer->str = ft_strjoin(lexer->str, str_env);
		lexer->her = 0;
	}
	i += len + 1;
	return (i);
}

int	token_env(char *input, int i, t_lexer *lexer)
{
	if (ft_isdigit(input[i + 1]))
		i += 2;
	else
		i = token_env2(input, i, lexer);
	return (i);
}
