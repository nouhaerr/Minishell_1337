# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hobenaba <hobenaba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 02:49:56 by nerrakeb          #+#    #+#              #
#    Updated: 2023/05/24 15:53:55 by hobenaba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 

CFLAGS = -Wall -Wextra -Werror

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