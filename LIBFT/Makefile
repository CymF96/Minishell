# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 14:18:02 by mcoskune          #+#    #+#              #
#    Updated: 2024/10/11 12:32:23 by mcoskune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar -rcs
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

HEADERS = ../minishell.h libft.h
.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@$(AR) $@ $^

$(OBJS): $(HEADERS)

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
