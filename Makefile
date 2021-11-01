# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 11:13:36 by mmasuda           #+#    #+#              #
#    Updated: 2021/11/01 12:14:37 by mmasuda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftstrtol.a

SRC_FILES := ft_strtol.c ft_strtol_utils.c ft_strtol_libft.c
SRC_DIR := srcs/
SRCS := $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS := $(SRCS:.c=.o)

INCLUDE := includes/

CC := gcc
CFLAGS := -Wall -Wextra -Werror

RM := rm -f

all : $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	ar rcs $@ $^

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
