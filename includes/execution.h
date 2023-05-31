/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:53:39 by hobenaba          #+#    #+#             */
/*   Updated: 2023/05/31 22:28:27 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// those functions are related to heredoc execution.

char    *her(t_data2 *heredoc, t_env *my_env);
void	exec_cmd(t_parser *parser);
void	exec_redir(t_parser *parser, t_data *my_heredoc);
void	start_exec(t_parser *parser, t_data *my_heredoc);

#endif