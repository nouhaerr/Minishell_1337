/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:48:37 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/31 23:13:01 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	sh_echo(t_parser **echo);
void	sh_pwd(void);
void	sh_env(void);
void	sh_exit(t_parser *ex);
void	redir(t_parser *parser);
void	sh_unset(t_data *arg);
void	sh_cd(t_parser *env_cmd);
void	cd_home(t_env *pwd_home, char **pwd, char **oldpwd, char *cwd);
void	cd_oldpwd(char **oldpwd, char **pwd);
void	cd_newpwd(t_data *name, char **oldpwd, char **pwd);

#endif
