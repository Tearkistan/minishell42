# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/20 16:20:40 by mnussler          #+#    #+#              #
#    Updated: 2025/09/20 16:20:42 by mnussler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = pipex

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Libft configuration
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRCS = main.c \
	files.c \
	commands.c \
	execute.c \
	cleanup.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = pipex.h

# Default target
all: $(NAME)

# Create the executable
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)
	rm -f *.txt
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean everything
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re 
