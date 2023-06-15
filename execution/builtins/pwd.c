/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 06:15:22 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/15 08:18:07 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_pwd(void)
{
	char	buf[4096];

	if (!getcwd(buf, 4096))
		perror("minishell");
	else
		printf("%s\n", buf);
}
