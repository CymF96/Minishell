# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 14:18:02 by mcoskune          #+#    #+#              #
#    Updated: 2024/07/10 14:23:15 by mcoskune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar -rcs
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@$(AR) $@ $^

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
