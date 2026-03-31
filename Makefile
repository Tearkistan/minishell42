# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/23 17:19:41 by psmolich          #+#    #+#              #
#    Updated: 2026/03/30 14:47:39 by twatson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME=minishell

INC_DIR=inc

LIBFT_DIR=libft

LIBFT=$(LIBFT_DIR)/libft.a
READLINE_LIBS = -lreadline -lhistory -lncurses

CC=cc -g
CFLAGS=-Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(INC_DIR) 

SRCS_PARSING_DIR := srcs_parsing

SRCS_PARSING := 	create_pipeline/add_arg.c \
					create_pipeline/add_pipe.c \
					create_pipeline/add_redir.c \
					create_pipeline/create_pipeline_from_tokens.c \
					create_pipeline/parse_word.c \
					parsing_utils/char_to_str.c \
					parsing_utils/ft_strjoin_free.c \
					parsing_utils/has_quotes.c \
					parsing_utils/is_redir.c \
					parsing_utils/is_special.c \
					parsing_utils/skip_whitespaces.c \
					tokenize_line/add_token_back.c \
					tokenize_line/add_token_pipe.c \
					tokenize_line/add_token_redir.c \
					tokenize_line/add_token_word.c \
					tokenize_line/check_token_syntax.c \
					tokenize_line/tokenize_line.c \
					parse_line.c \
					free_parsing.c

SRCS_EXECUTION_DIR := srcs_execution

SRCS_EXECUTION := 	builtin/builtin.c \
					builtin/builtin_utils.c \
					builtin/cd.c \
					builtin/cd_utils.c \
					builtin/exec_echo.c \
					builtin/exec_env.c \
					builtin/exec_pwd.c \
					builtin/exit.c \
					builtin/export.c \
					builtin/export_utils.c \
					builtin/export_utils_plus.c \
					builtin/unset.c \
					builtin/unset_utils.c \
					builtin/unset_utils_plus.c \
					heredoc/heredoc.c \
					heredoc/init_heredoc_mode.c \
					heredoc/count_heredoc.c \
					clean.c \
					main.c \
					error_msg.c \
					errors_main.c \
					path.c \
					exec_errors.c \
					redirects.c \
					redirects_utils.c \
					exec_pipeline.c \
					shell_init.c \
					exec_stateful.c \
					shell_loop.c \
					execute.c \
					signals.c \
					execute_utils.c \
					signals_utils.c

SRCS= 	$(addprefix $(SRCS_EXECUTION_DIR)/,$(SRCS_EXECUTION)) \
		$(addprefix $(SRCS_PARSING_DIR)/,$(SRCS_PARSING))

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME)  $(SRCS) $(LIBFT) $(READLINE_LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
