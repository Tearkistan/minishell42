# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 02:31:35 by mnussler          #+#    #+#              #
#    Updated: 2025/07/15 01:41:00 by mnussler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME = libft.a

# Compiler command
CC = cc
# -Wall: enable all warnings
# -Wextra: enable extra warnings
# -Werror: treat warnings as errors
# -I. : include the current directory in the search path for header files
# -Ift_printf: include ft_printf directory for header files
CFLAGS = -Wall -Wextra -Werror -I. -Ift_printf

# Archiver command
AR = ar
# r: replace or insert
# c: create
# s: create an index
ARFLAGS = rcs

# Source files for the mandatory part
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
				ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
				ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
				ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
				ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
				ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

# Source files for the bonus part
SRCS_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
							ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
							ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

# Source files for ft_printf
SRCS_PRINTF_BASE = ft_printf.c \
									 ft_parse_format_opts.c \
									 ft_print_utils.c \
									 ft_putchar.c \
									 ft_putlstr.c \
									 ft_putpad.c \
									 ft_putunbr.c \
									 ft_printf_str.c \
									 ft_printf_char.c \
									 ft_printf_unbr.c \
									 ft_printf_hex.c \
									 ft_printf_ptr.c \
									 ft_printf_nbr.c \
									 ft_printf_unbr_utils.c

SRCS_PRINTF = $(addprefix ft_printf/, $(SRCS_PRINTF_BASE))

# Object files derived from source files
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)

# Default rule
all: $(NAME)

# Create the static library
$(NAME): $(OBJS) $(OBJS_BONUS) $(OBJS_PRINTF)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(OBJS_BONUS) $(OBJS_PRINTF)

# Compile .c files to .o files
%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ft_printf .c files to .o files
ft_printf/%.o: ft_printf/%.c ft_printf/ft_printf.h libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_PRINTF)

# Clean the library file and object files
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

.PHONY: all clean fclean re 
