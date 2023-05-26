/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:48:37 by nerrakeb          #+#    #+#             */
/*   Updated: 2023/05/26 15:03:50 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	sh_echo(t_parser **echo);
void	sh_pwd(void);
void	sh_env(void);
void	sh_exit(t_parser *ex);
void	exec_cmd(t_parser *parser);
void	sh_unset(t_data *arg);

#endif
