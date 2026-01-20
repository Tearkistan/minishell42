NAME=minishell

SRC_DIR=src
INC_DIR=inc
OBJ_DIR=obj

LIBFT_DIR=libft

LIBFT=$(LIBFT_DIR)/libft.a
READLINE_LIBS = -lreadline -lhistory -lncurses

CC=cc -g # -g flag needs to be removed for submission!
CFLAGS=-Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(INC_DIR) 

SRC=main.c errors_main.c shell_init.c shell_loop.c clean.c parse.c execute.c \
exec_stateful.c exec_pipeline.c redirects.c path.c signals.c signals_utils.c \
exec_errors.c

SRCS= $(addprefix $(SRC_DIR)/,$(SRC))

OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re
