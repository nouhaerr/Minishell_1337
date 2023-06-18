/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:53:39 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/18 17:10:06 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef	struct s_pipe
{
	int	*rd_end;
	int	*wr_end;
} t_pipe;

// those functions are related to execution.
char	*her(t_data2 *heredoc, t_env *my_env);
void	run_builtin(t_parser *parser);
void	exec_heredoc(t_parser *parser, t_data **my_heredoc);
void	execution(t_parser *parser, t_data *my_heredoc);
int		multiple_pipes(t_parser *node);
int	    exec_cmd(t_parser *parser, t_pipe pip, char *msg);
int		isbuiltin(t_parser *parser);
int		*fd_redirection(t_parser *node);
char	*get_path(char *cmd);
void	ft_free(char **str);
void	ft_err(char *s, char *cmd, char *s2);

#endif