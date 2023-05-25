/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:46:12 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/24 18:59:26 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void her(t_data *heredoc)
{
    if (heredoc != NULL)
        printf("hello\n");
    printf("before segfault");
}
