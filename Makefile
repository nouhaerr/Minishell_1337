# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 02:49:56 by nerrakeb          #+#    #+#              #
#    Updated: 2023/05/24 16:49:44 by hobenaba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
# RDFLAGS = -L/Users/nerrakeb/goinfre/homebrew/opt/readline/include/readline -lreadline
SRCS =	main.c ft_lst_lex.c utils.c parse.c ft_lst_parse.c \
		env.c tokens.c init.c lexer.c words.c \
		my_free.c execution/builtins/echo.c execution/builtins/pwd.c \
		execution/builtins/env.c execution/builtins/exit.c \
		execution/start_session.c
OBJS = $(SRCS:.c=.o)
LIBFT= libft.a
LIBFT_DIR= libft/
NAME = minishell

SRCS = main.c ft_lst_lex.c utils.c parse.c ft_lst_parse.c env.c my_free.c lexer.c tokens.c init.c words.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "\033[0;35m your minishell is getting ready ...\033[0;0m"
	@make -C libft -s
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS)  -L libft/ -l ft -L libft/ft_printf/ -l ftprintf -lreadline

clean :
	@rm -rf $(OBJS) 
	@MAKE clean -C libft

fclean : clean
	@rm -rf $(NAME)
	@MAKE fclean -C libft
	@echo "\033[0;32m all clean\033[0;0m"

re : fclean all

.SILENT : $(OBJS)