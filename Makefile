NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O3
LDFLAGS = -lreadline -lncurses

SRC_PATH = ./
OBJ_PATH = obj/
LIBFT_PATH = ./LIBFT
LIBFT = $(LIBFT_PATH)/libft

SRC =	minishell.c \
		input_validate.c \
		exit_cleanup.c \
		clean_init.c \
		parse_input.c \


SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) all

bonus: all

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus
