/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:18:08 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/31 23:29:56 by nerrakeb         ###   ########.fr       */
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
			glb_var.exit_status = 1;
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
			return (free(cwd));
		}
		else if (oldpwd == NULL)
			ft_lstaddback_env(&glb_var.list, ft_lstnew_env(ft_strdup("OLDPWD"), cwd));
		else
			set_oldpwd(oldpwd, cwd);
		set_pwd(pwd);
		glb_var.exit_status = 0;
	}
	else
	{
		glb_var.exit_status = 1;
		return (printf("minishell: cd: HOME not set\n"), free(cwd));
	}
}

void	cd_oldpwd(char **oldpwd, char **pwd)
{
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		glb_var.exit_status = 1;
		printf("minishell: cd: OLDPWD not set\n");
		return(free(cwd));
	}
	else
	{
		if (chdir(*oldpwd) == -1)
		{
			glb_var.exit_status = 1;
			printf("minishell: cd: %s: %s\n",cwd, strerror(errno));
			return(free(cwd));
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

void	cd_newpwd(t_data *name, char **oldpwd, char **pwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (chdir(name->value) == -1)
	{
		glb_var.exit_status = 1;
		if (name->value[0] == '-' && name->value)
		{
			printf("minishell: cd: %s: invalid option\n", name->value);
			printf("cd: usage: cd [-L|-P] [dir]\n");
		}
		else
			printf("minishell: cd: %s: %s\n", name->value, strerror(errno));
		return(free(cwd));
	}
	else if (oldpwd == NULL)
		ft_lstaddback_env(&glb_var.list, ft_lstnew_env(ft_strdup("OLDPWD"), cwd));
	else
		set_oldpwd(oldpwd, cwd);
	set_pwd(pwd);
	glb_var.exit_status = 0;
}
