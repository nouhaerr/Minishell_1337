/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:53:39 by hobenaba          #+#    #+#             */
/*   Updated: 2023/06/21 18:12:41 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_pipe
{
	int	*rd_end;
	int	*wr_end;
}	t_pipe;

// those functions are related to execution.
void	her(t_data2 *heredoc, t_env *my_env, int *pipefd);
void	run_builtin(t_parser *parser);
void	exec_heredoc(t_parser *parser);
void	execution(t_parser *parser, t_data *my_heredoc);
int		multiple_pipes(t_parser *node);
int		exec_cmd(t_parser *parser, t_pipe pip, char *msg);
int		isbuiltin(t_parser *parser);
void	builtin_executor(t_parser *node, t_pipe pip, char *msg);
void	run_builtin(t_parser *parser);
int		*dup_and_exec(t_parser *parse, t_pipe pip, char *msg);
int		*fd_redirection(t_parser *node);
char	*get_path(char *cmd);
char	**create_env_arr(int size);
char	**table_cmd(t_parser *node);
void	ft_free(char **str);
void	ft_err(char *s, char *cmd, char *s2);
void	update_fd(int *my_fd);

#endif