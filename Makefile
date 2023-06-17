# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 02:49:56 by nerrakeb          #+#    #+#              #
#    Updated: 2023/06/17 20:24:51 by nerrakeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
RDFLAGS +=  -lreadline -L/goinfre/nerrakeb/homebrew/opt/readline/lib
INCLUDES += -I /goinfre/nerrakeb/homebrew/opt/readline/include
#RDFLAGS +=  -lreadline -L /Users/hobenaba/goinfre/homebrew/opt/readline/lib -lreadline
#INCLUDES += -I /Users/hobenaba/goinfre/homebrew/opt/readline/include/readline
SRCS =	main.c parsing/my_free.c parsing/ft_lst_one.c \
		parsing/utils.c parsing/parse.c parsing/init.c \
		parsing/ft_lst_second.c parsing/words.c  \
		parsing/env.c parsing/tokens.c parsing/lexer.c \
		execution/builtins/echo.c execution/builtins/pwd.c \
		execution/builtins/env.c execution/builtins/exit.c \
		execution/redirections/her.c execution/builtins/utils.c \
		execution/builtins/unset.c execution/builtins/cd.c \
		 execution/builtins/export/export.c \
		execution/builtins/export/modifie_and_add.c execution/builtins/export/check_exp.c \
		execution/builtins/export/exp_utils.c execution/execution.c \
		execution/exec_bltn_hered.c signal.c execution/exec_cmd.c \
		execution/redirections/files.c execution/begin_exec.c \
		execution/exec_pipes.c
		
OBJS = $(SRCS:.c=.o)
LIBFT= libft.a
LIBFT_DIR= libft/
NAME = minishell

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(INCLUDES) $(RDFLAGS) -lreadline 
	@echo "\033[0;93m- your minishell is getting ready ...\033[0m"

$(LIBFT): $(LIBFT_DIR)libft.h
	@$(MAKE) -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)$(LIBFT) .

all : $(NAME)

clean :
	rm -rf $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "\033[1;31m- Object files removed!\033[0m"

fclean : clean
	rm -rf $(NAME)
	@rm -f $(LIBFT)
	@echo "\033[1;31m all clean\033[0;0m"

re : fclean all

.SILENT : $(OBJS)

.PHONY: all clean fclean re