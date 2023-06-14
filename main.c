/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:52:25 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/14 12:14:42 by nerrakeb         ###   ########.fr       */
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
		return (printf("minishell: syntax error near unexpected token \n"), 1);
	while (tokens2)
	{
		if (tokens2 -> type == the_pipe
			&& (previous == NULL || tokens2 -> next == NULL))
			return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
		if ((tokens2 -> type != the_pipe && tokens2 -> type != word)
			&& (tokens2 -> next == NULL || (tokens2 -> next)-> type != word))
			return (printf("minishell: syntax error near unexpected token `newline'\n"), 1);
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
	t_data 	*my_heredoc;
	int			base;
	(void)ac;
	(void)av;
	(void)env;

	lexer = malloc(sizeof(t_lexer));
	glb_var.list = save_my_env(env); //->> this one is where id o have leaks
	system("leaks minishell");
	my_heredoc = NULL;
	while (1)
	{
		tokens = NULL;
		parser = NULL;
		prompt = get_prompt(getcwd(NULL, 0));
		input = readline(prompt);
		free((void *)prompt);
		if (input == NULL)
			break ;
		if (ft_strcmp(input, "") != 0)
			add_history(input);
		base = lex(input, &tokens, lexer);
		if (!syntax_error(base, &tokens) && tokens != NULL)
		{
			parse(&tokens, &parser, lexer);
			execution(parser, my_heredoc);
			free_mylist(parser, 1);
		}
		else
			glb_var.exit_status = 1;
		free_mylist(tokens, 0);
		free(input);
	}
}