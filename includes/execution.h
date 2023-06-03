/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:53:39 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/04 00:15:39 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// those functions are related to execution.

char    *her(t_data2 *heredoc, t_env *my_env);
void	exec_builtin(t_parser *parser);
void	exec_redir(t_parser *parser, t_data *my_heredoc);
void	execution(t_parser *parser, t_data *my_heredoc);
void	exec_cmd(t_parser *parser);

#endif