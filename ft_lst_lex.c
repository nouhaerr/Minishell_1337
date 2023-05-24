/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:01:22 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 10:53:20 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token	*ft_lstnew(char *value, enum t_enum type, enum t_type arten)
{
	t_token	*p;

	p = malloc(sizeof (t_token));
	if (!p)
		return (NULL);
	p -> value = value;
	p ->type = type;
	p -> arten = arten;
	p -> next = NULL;
	return (p);
}

void	ft_lstaddback(t_token **lst, t_token *new)
{
	t_token	*p;

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
