# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 02:48:29 by nerrakeb          #+#    #+#              #
#    Updated: 2023/05/24 11:47:22 by nerrakeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror 
IMP = ft_atoi.c	ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c	ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_split.c ft_strtrim.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c	ft_putnbr_fd.c ft_strcmp.c ft_atoi2.c ft_strjoin2.c \
	ft_lstadd_front.c ft_lstlast.c ft_lstsize.c ft_dostrlen.c my_countnbr.c \
	#get_next_line/get_next_line_utils.c get_next_line/get_next_line.c

OBJ = $(IMP:.c=.o)
NAME = libft.a

%.o:%.c
	$(CC) $(CFLAGS) -c $<

all	: $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
