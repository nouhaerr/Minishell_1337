/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:45:51 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 10:54:13 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_data	*ft_lstnew2(char *value)
{
	t_data	*p;

	p = malloc(sizeof (t_data));
	if (!p)
		return (NULL);
	p -> value = value;
	p -> next = NULL;
	return (p);
}

void	ft_lstaddback2(t_data **lst, t_data *new)
{
	t_data	*p;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	if (!p)
		return ;
	while (p-> next)
		p = p -> next;
	p -> next = new;
}

t_parser	*ft_lstnew3(void) // for the main struct
{
	t_parser	*p;

	p = malloc(sizeof (t_parser));
	if (!p)
		return (NULL);
	p -> next = NULL;
	p -> args = NULL;
	p -> cmd = NULL;
	p -> outfiles = NULL;
	p -> infiles = NULL;
	p -> heredoc = NULL;
	return (p);
}

t_parser	*ft_lstaddback3(t_parser **lst, t_parser *new) // for the main struct.
{
	t_parser	*p;

	if (*lst == NULL)
	{
		*lst = new;
		return (new);
	}
	p = *lst;
	if (!p)
		return (NULL);
	while (p-> next)
		p = p -> next;
	p -> next = new;
	return (new);
}
//utiils for me and only.
//this function is just to guide me// no need of it in the code itself
int	ft_lstsize_parse(t_parser *parse)
{
	int	i;

	i = 0;
	if (!parse)
		return (0);
	while (parse)
	{
		i++;
		parse = parse -> next;
	}
	return (i);
}
// this one to check the output of my main struct
void	check_struct(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		t_data2 *out = parser -> outfiles;
		t_data *her = parser -> heredoc;
		t_data *in = parser -> infiles;
		t_data2 *args = parser -> args;
		t_data *cmd = parser -> cmd;
		printf("struct number %d\n", ++i);
		while(out)
		{
			printf("[out : %s, type : %d]\n", (out) -> value, (out) -> type);
			(out) = (out) -> next;
		}
		while (her)
		{
			printf("here : [%s]\n ", (her) -> value);
			(her) = (her) -> next;
		}
		while (in)
		{
			printf("input : [%s]\n ", (in) -> value);
			(in) = (in) -> next;
		}
		while (cmd)
		{
			printf("cmd: [%s]\n", (cmd) -> value);
			(cmd) = (cmd) -> next;
		}
		while (args)
		{
			printf("args : [%s], type : %d\n", (args) -> value, args -> type);
			(args) = (args) -> next;
		}
		parser = parser -> next;
		
	}
}
