NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -O0
LDFLAGS     = -lreadline -lncurses

LIBFT_PATH  = INC/LIBFT/
LIBFT       = $(LIBFT_PATH)libft
HEADER      = INC/minishell.h

OBJ_PATH    = ./OBJ/
INC_PATH    = ./INC/
SRC_PATH    = ./SRC/

CFILES =	minishell.c\
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
			UTILS/utils_3.c\
			UTILS/pexe_sorting.c\
			UTILS/check_exit.c

SRCS    = $(addprefix $(SRC_PATH), $(CFILES))
OBJ     = $(CFILES:.c=.o)
OBJS    = $(addprefix $(OBJ_PATH), $(OBJ))
INC     = -I $(INC_PATH) -I $(LIBFT_PATH)

.PHONY: all clean fclean re $(LIBFT)

all: $(OBJ_PATH) $(LIBFT) $(NAME)

# Create obj directory and subdirectories
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/EXECUTION
	@mkdir -p $(OBJ_PATH)/PARSE
	@mkdir -p $(OBJ_PATH)/UTILS

# Build libft
$(LIBFT):
	@echo "Building libft"
	@make -C $(LIBFT_PATH) all

# Compile .c to .o into the obj folder
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Link everything into the final executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)
	@echo "Making Minishell"

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo "Cleaning Minishell"

re: fclean all
