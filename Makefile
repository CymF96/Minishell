NAME = minishell
CC = gcc #made gcc to make it work in my compiler
CFLAGS = -Wall -Wextra -Werror -g3 -O3 -O0
LDFLAGS = -lreadline -lncurses

SRC_PATH = ./
LIBFT_PATH = ./LIBFT
LIBFT = $(LIBFT_PATH)/libft

SRC =	minishell.c\
		PARSE/parse_create_modified.c \
		PARSE/parse_env_variables.c \
		PARSE/parse_heredoc.c \
		PARSE/parse_heredoc_helper.c \
		PARSE/parse_main.c \
		PARSE/parse_mallocs.c \
		PARSE/parse_pexe.c \
		PARSE/parse_pexe_cleaner.c \
		PARSE/parse_specials.c \
		PARSE/parse_tokenize.c \
		PARSE/parse_utils.c \
		PARSE/parse_wild_character.c \
		EXECUTION/exe_builtin_cmd_1.c\
		EXECUTION/exe_builtin_cmd_2.c\
		EXECUTION/exe_executable.c\
		EXECUTION/exe_fork.c\
		EXECUTION/exe_handle_signals.c\
		EXECUTION/exe_exit_error.c\
		EXECUTION/exe_main.c\
		EXECUTION/exe_pipe.c\
		EXECUTION/exe_redirection.c\
		UTILS/clean_init.c\
		UTILS/clean_structures.c\
		UTILS/envp_utils.c\
		UTILS/exit_cleanup.c\
		UTILS/utils.c\
		UTILS/utils_2.c\
		UTILS/pexe_sorting.c\

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
