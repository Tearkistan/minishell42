# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/29 10:11:16 by psmolich          #+#    #+#              #
#    Updated: 2026/01/06 14:34:56 by psmolich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

.PHONY: all clean fclean re

LIB := libft.a

BASIC := ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_strdup.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

EXTRA := ft_atol.c \
		ft_strstr.c \
		ft_strcmp.c \
		ft_isspace.c \
		ft_isallspaces.c \
		ft_isalldigits.c \
		ft_free_arr.c \
		ft_bitcount.c
		
PRINTF := ft_printf_check.c \
		ft_printf.c \
		ft_put_c_s.c \
		ft_put_int.c \
		ft_put_uint_ptr.c
		
GNL := ft_get_next_line.c

SRCS := $(BASIC) $(EXTRA) $(PRINTF) $(GNL)

OBJS := $(patsubst %.c, %.o, $(SRCS))

CC := cc
CFLAGS := -Wall -Wextra -Werror

all: $(LIB)

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)
	make clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB)

re: fclean all
