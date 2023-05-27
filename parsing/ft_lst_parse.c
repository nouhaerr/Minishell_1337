/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:45:51 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/27 17:46:34 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_parser	*ft_lstnew3(void)
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

t_parser	*ft_lstaddback3(t_parser **lst, t_parser *new)
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

t_data2	*ft_lstnew4(char *value, enum t_e type)
{
	t_data2	*p;

	p = malloc(sizeof (t_data2));
	if (!p)
		return (NULL);
	p -> value = value;
	p ->type = type;
	p -> next = NULL;
	return (p);
}

void	ft_lstaddback4(t_data2 **lst, t_data2 *new)
{
	t_data2	*p;

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
