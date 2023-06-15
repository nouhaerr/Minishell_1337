/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 06:15:22 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/06/15 07:59:34 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_pwd(void)
{
	char	buf[4096];
	//Mémoire tampon pour stocker le répertoire de travail actuel
	/*Maximum number of bytes in a pathname,
	including the terminating null character.*/
	//the PATH_MAX = 4096bytes  that is supported by the operating system linux.
	if (!getcwd(buf, 4096))
		perror("minishell");
	else
		printf("%s\n", buf);
}
