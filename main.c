/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:52:25 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/26 16:07:26 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	syntax_error(int base, t_token **tokens)
{
	t_token	*t;
	t_token	*p;

	p = NULL;
	if (*tokens == NULL)
		t = NULL;
	else
		t = *tokens;
	if (base != 0)
		return (printf("minishell: syntax error near unexpected token\n"), 1);
	while (t)
	{
		if ((t -> type == the_pipe && (p == NULL || t->next == NULL))
			|| (t->type == the_pipe && (t->next)->type == the_pipe))
			return (printf("minishell: syntax error near unexpected token `|'\n")
				, 1);
		if ((t -> type != the_pipe && t -> type != word)
			&& (t -> next == NULL || (t -> next)-> type != word))
			return (printf("minishell: syntax error near unexpected token\n"),
				1);
		p = t;
		t = t -> next;
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
	{
		
		cwd = ft_strdup("\e[1;95m!!->/minishell => \e[0m ");
	}
	return (cwd);
}

void	pa_ex(t_token *tok, t_lexer *lex, t_parser *par)
{
	parse(&tok, &par, lex);
	if (par -> nu_here >= 17)
	{
		printf("minishell: maximum here-document count exceeded\n");
		exit (2);
	}
	execution(par);
	update_fd(g_var.fd_prog);
	free_mylist(par, 1);
}

int	_session(t_token *tok, t_parser *par, t_lexer *le)
{
	char		*input;
	const char	*prompt;
	int			base;

	(void)le;
	while (1)
	{	
		tok = NULL;
		par = NULL;
		g_var.signal_heredoc =  0;
		signal_check();
		prompt = get_prompt(getcwd(NULL, 0));
		input = readline(prompt);
		signal(SIGINT, SIG_IGN);
		free((void *)prompt);
		if (input == NULL)
			break ;
		if (ft_check_space(input))
		{
			add_history(input);
			g_var.fd_prog = my_fd(); // HERE THERE IS A LEAK
			base = lex(input, &tok, le);
			if (!syntax_error(base, &tok) && tok != NULL)
				pa_ex(tok, le, par);
			else
				g_var.exit_status = 258;
			close_myfd_prog(g_var.fd_prog);
			free_mylist(tok, 0);
		}
		free(input);
	}
	return (g_var.exit_status);
}

int	main(int ac, char **av, char **env)
{
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
	if (!env_search(g_var.list, "PWD"))
		ft_lstaddback_env(&g_var.list,
			ft_lstnew_env(ft_strdup("PWD"), getcwd(NULL, 0)));
	out = _session(tokens, parser, lexer);
	return (out);
}
