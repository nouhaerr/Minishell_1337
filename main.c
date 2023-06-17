/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:52:25 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/17 19:17:17 by nerrakeb         ###   ########.fr       */
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
		return (printf("minishell: syntax error near unexpected token\n"), 1);
	while (tokens2)
	{
		if (tokens2 -> type == the_pipe
			&& (previous == NULL || tokens2 -> next == NULL))
			return (printf("minishell: syntax error near unexpected token `|'\n")
				, 1);
		if ((tokens2 -> type != the_pipe && tokens2 -> type != word)
			&& (tokens2 -> next == NULL || (tokens2 -> next)-> type != word))
			return (printf("minishell: syntax error near unexpected token\n"),
				1);
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

void	pa_ex(t_token *tok, t_lexer *lex, t_parser *par, t_data *here)
{
	parse(&tok, &par, lex);
	execution(par, here);
	free_mylist(par, 1);
}

int	_session(t_token *tok, t_parser *par, t_data *her, t_lexer *le)
{
	char		*input;
	const char	*prompt;
	int			base;

	while (1)
	{	
		tok = NULL;
		par = NULL;
		signal_check();
		prompt = get_prompt(getcwd(NULL, 0));
		input = readline(prompt);
		free((void *)prompt);
		if (input == NULL)
			break ;
		if (ft_strcmp(input, "") != 0)
			add_history(input);
		base = lex(input, &tok, le);
		if (!syntax_error(base, &tok) && tok != NULL)
			pa_ex(tok, le, par, her);
		else
			g_var.exit_status = 1;
		free_mylist(tok, 0);
		free(input);
	}
	return (g_var.exit_status);
}

int	main(int ac, char **av, char **env)
{
	t_data		*my_heredoc;
	t_lexer		*lexer;
	t_token		*tokens;
	t_parser	*parser;
	int			out;
	
	(void)ac;
	(void)av;
	lexer = malloc (sizeof(t_lexer));
	tokens = NULL;
	parser = NULL;
	g_var.list = save_my_env(env);
	my_heredoc = NULL;
	out = _session(tokens, parser, my_heredoc, lexer);
	return (out);
}
