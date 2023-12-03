NAME     = minishell
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g

HDRS_DIR = ./inc/
SRC_DIR  = ./src
OBJ_DIR  = ./obj

LIBFT_DIR = ./libft
LIBFT     = $(LIBFT_DIR)/libft.a

SRCS     = $(SRC_DIR)/main.c \
           $(SRC_DIR)/non_print_off.c \
           $(SRC_DIR)/signals.c \
		   $(SRC_DIR)/parsing_begins.c \
		   $(SRC_DIR)/temp_arg_array.c \
		   $(SRC_DIR)/numeric_map_parse.c \
		   $(SRC_DIR)/input_validity_checks.c \
		   $(SRC_DIR)/env_structuring.c \
		   $(SRC_DIR)/map_comm_pip_redir.c \
		   $(SRC_DIR)/comm_struc_make.c \
		   $(SRC_DIR)/interpreting_subwords.c \
		   $(SRC_DIR)/chop_and_reconstruct_word.c \
		   $(SRC_DIR)/execution.c \
		   $(SRC_DIR)/test_execution.c  \
		   $(SRC_DIR)/com_struc_docs.c \
		   $(SRC_DIR)/com_struc_inputs.c

HDRS     = -I $(HDRS_DIR) -I /usr/local/Cellar/readline/8.1.1/include/
LIBS     = -L /usr/local/Cellar/readline/8.1.1/lib/
OBJS     = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) libft
	@echo "Program \"$(NAME)\" compilation:"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS) -lreadline $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HDRS) -c $^ -o $@

libft:
	@make all --quiet -C $(LIBFT_DIR)
	@clear

clean:
	@make clean --quiet -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean --quiet -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft