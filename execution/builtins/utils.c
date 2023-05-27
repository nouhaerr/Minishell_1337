/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:18:08 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/27 18:52:13 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	cd_home(t_env *pwd_home)
{
	char *path;

	path = NULL;
	if (pwd_home)
		path = pwd_home->value;
	if (path)
	{
		if (chdir(path) == -1)
		{
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
			glb_var.exit_status = 1;
			return ;
		}
		glb_var.exit_status = 0;
	}
	else
	{
		printf("minishell: cd: HOME not set\n");
		glb_var.exit_status = 1;
	}	
}

void	cd_oldpwd(char **oldpwd, char **pwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		glb_var.exit_status = 1;
	}
	else
	{
		if (chdir(*oldpwd) == -1)
		{
			printf("minishell: cd: %s: %s\n",cwd, strerror(errno));
			glb_var.exit_status = 1;
			return ;
		}
	}
}
