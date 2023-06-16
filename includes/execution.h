/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:53:39 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/16 16:36:25 by hobenaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// those functions are related to execution.
char	*her(t_data2 *heredoc, t_env *my_env);
void	exec_builtin(t_parser *parser);
void	exec_heredoc(t_parser *parser, t_data *my_heredoc);
void	execution(t_parser *parser, t_data *my_heredoc);
int		exec_cmd(t_parser *parser, int fd[2], char *msg);
int		isbuiltin(t_parser *parser);
int		*fd_redirection(t_parser *node);
char	*get_path(char *cmd);

#endif