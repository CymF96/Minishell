NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O3
LDFLAGS = -lreadline -lncurses

SRC_PATH = ./
LIBFT_PATH = ./LIBFT
LIBFT = $(LIBFT_PATH)/libft

SRC =	minishell.c\
		PARSE/parse_main.c\
		PARSE/parse_utils.c\
		EXECUTION/exe_builtin_cmd_1.c\
		EXECUTION/exe_builtin_cmd_2.c\
		EXECUTION/exe_execution.c\
		EXECUTION/exe_exit.c\
		UTILS/clean_init.c\
		UTILS/exit_cleanup.c\
		UTILS/input_validate.c\

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(OBJ)

%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) all

bonus: all

clean:
	@rm -rf $(OBJ)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus
