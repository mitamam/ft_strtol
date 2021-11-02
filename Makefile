# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 11:13:36 by mmasuda           #+#    #+#              #
#    Updated: 2021/11/02 11:24:45 by mmasuda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftstrtol.a

SRCS := ft_strtol.c ft_strtol_utils.c ft_strtol_libft.c
OBJS := $(SRCS:.c=.o)

CC := gcc
CFLAGS := -Wall -Wextra -Werror

RM := rm -f

all : $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	ar rcs $@ $^

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
