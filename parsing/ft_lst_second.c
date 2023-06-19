/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_second.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:45:51 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/19 11:27:38 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*ft_lstnew2(char *value)
{
	t_data	*p;

	p = malloc(sizeof (t_data));
	if (!p)
		return (NULL);
	p -> value = ft_strdup(value);
	p -> next = NULL;
	return (p);
}

void	ft_lstaddback2(t_data **lst, t_data *new)
{
	t_data	*p;

	//printf("address : %p\n", *lst);
	if (*lst == NULL)
	{
		*lst = new;
		//printf ("%s\n", new -> value);
		return ;
	}
	p = *lst;
	if (!p)
		return ;
	//rintf("->>>> %s\n", p -> value);
	while (p-> next)
		p = p -> next;
	p -> next = new;
}

t_parser	*ft_lstnew3(int index)
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
	p -> index = index;
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
