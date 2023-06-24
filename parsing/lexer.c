/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:53:34 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/24 18:39:38 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_which_special_char(char c, char next_c, t_token **tokens, t_lexer *lexer)
{
	if (c == '|')
		return (lexer -> index++, ft_lstaddback(tokens, ft_lstnew(ft_strdup("|"),
					the_pipe, general)), 1);
	else if (c == '>')
	{
		if (next_c == '>')
			return (ft_lstaddback(tokens,
					ft_lstnew(ft_strdup(">>"), dr_rdr, general)), 2);
		return (ft_lstaddback(tokens,
				ft_lstnew(ft_strdup(">"), r_rdr, general)), 1);
	}
	else if (c == '<')
	{
		if (next_c == '<')
			return (ft_lstaddback(tokens,
					ft_lstnew(ft_strdup("<<"), heredoc, general)), 2);
		return (ft_lstaddback(tokens,
				ft_lstnew(ft_strdup("<"), l_rdr, general)), 1);
	}	
	return (0);
}

int	ft_check_space(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i + 1] == ' ')
			j++;
		else if (s[i] != ' ' && s[i + 1] == '\0')
			j++;
		i++;
	}
	return (j);
}

void	build_list(t_lexer *lexer, t_token **tokens)
{
	int		arten;
	// char	**str;
	// int		i;

	if (lexer -> base2 != 0)
		arten = quotes;
	else
		arten = general;
	
	if (lexer -> str != NULL && !ft_strcmp(lexer -> str, " "))
		ft_lstaddback(tokens, ft_lstnew(lexer -> str, word, env_general));
	// if (arten == general && ft_check_space(lexer -> str))
	// {
		// str = ft_split(lexer -> str, ' ');
		// i = 0;
		// while (str[i])
		// {	
		// 	if (lexer -> base == 0)
		// 		ft_lstaddback(tokens, ft_lstnew(str[i], word, env_general));
		// 	else
		// 		ft_lstaddback(tokens, ft_lstnew(str[i], word, env_quotes));
		// 	i++;
	// 	}
	// }
	else
		ft_lstaddback(tokens, ft_lstnew(lexer -> str, word, arten));
	lexer -> str = NULL;
	lexer -> base2 = 0;
}

int	check_condition(t_lexer *lexer, char *input, int i)
{
	if (input[i] == lexer -> c && input[i - 1] == lexer -> c
		&& (lexer -> str == NULL
			&& (input[i + 1] == ' ' || input[i + 1] == '\0' )))
		return (1);
	return (0);
}

int	lex(char *input, t_token **tokens, t_lexer *lexer)
{
	int	i;

	i = 0;
	lexer_init(lexer);
	while (input[i])
	{
		if (input[i] == ' ' && lexer -> base == 0)
			i = ft_ignore_spaces(input, i);
		if (input[i] != '\0' && ft_strchr("$|><", input[i]) != NULL && lexer -> base == 0)
		{
			if (input[i] == '<' && input[i + 1] == '<')
				lexer -> her = 1;
			i += check_which_special_char(input[i], input[i + 1], tokens, lexer);
		}
		else if (input[i] != '\0')
			i = partition_tokens(lexer, input, i);
		if (input[i] != '\0' && check_condition(lexer, input, i) == 1)
			lexer -> str = ft_strjoin(lexer -> str, ft_substr(input, i - 1, 2));
		if (input[i] == '$')
			i = token_env(input, i, lexer, tokens);
		// printf("hier : lexer -> str:%s\n", lexer -> str);
		// sleep (1);
		if (lexer -> base == 0 && lexer -> str != NULL && (input [i] == '\0'
				|| ft_strchr(" |><", input[i]) != NULL))
			build_list(lexer, tokens);
	}
	return (free(lexer -> str), lexer -> base);
}
