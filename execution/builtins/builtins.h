/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:48:37 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/24 17:44:13 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	sh_echo(t_parser **echo);
void	sh_pwd(void);
void	sh_env(t_env *env_cmd);
void	sh_exit(t_parser *ex);
void	sh_unset(t_env *myenv, char **arg);
void	exec_cmd(t_parser *parser);

#endif
