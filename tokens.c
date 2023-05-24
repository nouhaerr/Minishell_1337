/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:33:59 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 10:55:12 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_which_special_char(char c, char next_c, t_token **tokens)
{
	if (c == '|')
		return (ft_lstaddback(tokens, ft_lstnew(ft_strdup("|"), the_pipe, general)), 1);
	else if (c == '>')
	{
		if (next_c == '>')
			return (ft_lstaddback(tokens, ft_lstnew(ft_strdup(">>"), dr_rdr, general)), 2);
		return (ft_lstaddback(tokens, ft_lstnew(ft_strdup(">"), r_rdr, general)), 1);
	}
	else if(c == '<')
	{
		if (next_c == '<')
			return (ft_lstaddback(tokens, ft_lstnew(ft_strdup("<<"), heredoc, general)), 2);
		return (ft_lstaddback(tokens, ft_lstnew(ft_strdup("<"), l_rdr, general)), 1);
	}	
	return(0);	
}

int	ft_check_word(char *input, int start, int base)
{
	int		j;
	int		i;
	char	c;
	
	j = 0;
	i = 0;
	if (base < 0)
	{
		while (input[start] && ft_isalnum(input[start]) == 1)
		{
			j++;
			start++;
		}
	}
	else if (base == 0)
	{
		while (input[start] && ft_strchr(" $|><\'\"", input[start]) == NULL)
		{
			j++;
			start++;
		}
	}
	else
	{
		if (base == 1)
			c = '\'';
		else
			c = '\"';
		while (input[start] && input[start] != c)
		{
			if (base == 2 && input[start] == '$')
				break;
			j++;
			start++;
		}
	}
	return (j);
}

int	token(char *input, t_token **tokens, t_env *my_envs, int exit_status)
{
	int		i;
	int		len;
	int		base;
	int		base2;
	char	*str;
	char	*str_env;
	int		her;
	char	c;
	char	*env;
	char	*itoa;
	int		a;
	
	i = 0;
	base = 0;
	a = 0;
	her = 0;
	str = NULL;
	base2 = base;
	while (input[i])
	{
		if (input[i] == ' ')
			i = ft_ignore_spaces(input, i);
		if (ft_strchr("$|><", input[i]) != NULL && base == 0)
		{
			if (input[i] == '<' && input[i + 1] == '<')
				her = 1;
			i += check_which_special_char(input[i],input[i + 1], tokens);
		}
		else if (a == 0 && (input[i] == '\'' || input[i] == '\"'))
		{
			c = input[i];
			a = 1;
			if(input[i] == '\'')
				base = 1;
			else
				base = 2;
			base2 = base;
			i++;
		}
		else if (c == input[i])
		{
			base = 0;
			a = 0;
			i++;
		}
		else if (input [i] != '\0')
		{
			len = ft_check_word(input, i, base);
			if (base == 0 && input[i] == '#')
				i += len;
			else 
				str = ft_strjoin(str, ft_substr(input, i, len));
			i += len;
		}
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				itoa = ft_itoa(exit_status);
				str_env = ft_strdup(itoa);
				str = ft_strjoin(str, str_env);
				free(itoa);
				i += 2;
			}
			else
			{
				len = ft_check_word(input, i + 1, -1);
				if (her == 0 && (base == 2 || base == 0))
				{
					if (len != 0)
					{
						env = ft_substr(input, i + 1, len);
						str_env = check_env(env, my_envs);
						free(env);
					}
					if (len == 0)
						str_env = ft_strdup("$");
					str = ft_strjoin(str, str_env);
				}
				else 
				{
					str_env = ft_substr(input, i, len + 1);
					str = ft_strjoin(str, str_env);
					her = 0;
				}
				i += len + 1;
			}
		}
		if (str != NULL && (input [i] == '\0' || ft_strchr(" |><", input[i]) != NULL))
		{
			int arten;
			if(base2 != 0)
				arten = quotes;
			else
				arten = general;
			ft_lstaddback(tokens, ft_lstnew(str, word, arten));
			str = NULL;
			base2 = 0;
		}
	}
	return (base);
}
