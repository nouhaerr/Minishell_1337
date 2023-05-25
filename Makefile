# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 02:49:56 by nerrakeb          #+#    #+#              #
#    Updated: 2023/05/25 14:37:55 by nerrakeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
# RDFLAGS = -L/Users/nerrakeb/goinfre/homebrew/opt/readline/include/readline -lreadline
SRCS =	main.c ft_lst_lex.c utils.c parse.c ft_lst_parse.c \
		env.c tokens.c init.c lexer.c words.c \
		my_free.c execution/builtins/echo.c execution/builtins/pwd.c \
		execution/builtins/env.c execution/builtins/exit.c \
		execution/builtins/unset.c execution/start_session.c
OBJS = $(SRCS:.c=.o)
LIBFT= libft.a
LIBFT_DIR= libft/
NAME = minishell

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)
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