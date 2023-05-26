/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:52:25 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/26 15:20:40 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	syntax_error(int base, t_token **tokens)
{
	t_token	*tokens2;
	t_token	*previous;

	previous = NULL;
	if (*tokens == NULL)
		tokens2 = NULL;
	else
		tokens2 = *tokens;
	if (base != 0)
		return (printf("Error : unclosed quotes\n"), 1);
	while (tokens2)
	{
		if (tokens2 -> type == the_pipe
			&& (previous == NULL || tokens2 -> next == NULL))
			return (printf("Error : syntax error\n"), 1);
		if ((tokens2 -> type != the_pipe && tokens2 -> type != word)
			&& (tokens2 -> next == NULL || (tokens2 -> next)-> type != word))
			return (printf("Error : syntax error\n"), 1);
		previous = tokens2;
		tokens2 = tokens2 -> next;
	}
	return (0);
}

char	*get_prompt(char *s)
{
	char	*workingdirectory_path;
	char	*cwd;

	cwd = NULL;
	if (s)
	{
		workingdirectory_path = ft_strrchr(s, '/');
		workingdirectory_path = ft_strjoin2("\e[1;95m->", workingdirectory_path);
		cwd = ft_strjoin2(workingdirectory_path, "\e[0m\e[1;95m=> \e[0m ");
		free(workingdirectory_path);
		free(s);
	}
	else
		cwd = ft_strdup("\e[1;95m!!->/minishell => \e[0m ");
	return (cwd);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	const char	*prompt;
	t_token		*tokens;
	t_lexer		*lexer;
	t_parser	*parser;
	int			base;

	(void)ac;
	(void)av;
	lexer = malloc(sizeof(t_lexer));
	glb_var.list = save_my_env(env);
	while (1)
	{
		tokens = NULL;
		parser = NULL;
		prompt = get_prompt(getcwd(NULL, 0));
		input = readline(prompt);
		free((void *)prompt);
		if (input == NULL)
			break ;
		add_history(input);
		base = lex(input, &tokens, lexer);
		if (!syntax_error(base, &tokens))
		{
			parse(&tokens, &parser, lexer);
			exec_cmd(parser);
			free_mylist(parser, 1);
		}
		else
			glb_var.exit_status = 1;
		free_mylist(tokens, 0);
		free(input);
	}
}
