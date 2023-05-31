/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:18:08 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/31 03:10:42 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pwd(char **pwd)
{
	if (pwd)
	{
		free(*pwd);
		*pwd = getcwd(NULL, 0);
	}
}

void	set_oldpwd(char **oldpwd, char *cwd)
{
	free(*oldpwd);
	*oldpwd = cwd;
}

void	cd_home(t_env *pwd_home, char **pwd, char **oldpwd, char *cwd)
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
		else if (oldpwd != NULL)
			set_oldpwd(oldpwd, cwd);
		set_pwd(pwd);
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
			return ;
	}
	else
	{
		if (chdir(*oldpwd) == -1)
		{
			printf("minishell: cd: %s: %s\n",cwd, strerror(errno));
			glb_var.exit_status = 1;
			return ;
		}
		else
		{
			printf("%s\n", *oldpwd);
			set_oldpwd(oldpwd, cwd);
		}
		set_pwd(pwd);
		glb_var.exit_status = 0;
	}
}
