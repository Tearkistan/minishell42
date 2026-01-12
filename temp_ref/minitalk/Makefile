# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 11:47:59 by psmolich          #+#    #+#              #
#    Updated: 2025/08/29 10:54:35 by psmolich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

.PHONY: all basic bonus clean fclean re re_b
.DEFAULT_GOAL := basic

SERVER := server
CLIENT := client
SERVER_B := server_bonus
CLIENT_B := client_bonus

LIB := libft/libft.a

SV_SRCS := server.c
CL_SRCS := client.c
SVB_SRCS := server_bonus.c
CLB_SRCS := client_bonus.c

CC := cc
CFLAGS := -Wall -Wextra -Werror

all: basic bonus

basic: $(SERVER) $(CLIENT)

bonus: $(SERVER_B) $(CLIENT_B)

$(SERVER): $(LIB)
	$(CC) $(CFLAGS) -o $(SERVER) $(SV_SRCS) $(LIB)

$(CLIENT): $(LIB)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CL_SRCS) $(LIB)
	
$(SERVER_B): $(LIB)
	$(CC) $(CFLAGS) -o $(SERVER_B) $(SVB_SRCS) $(LIB)

$(CLIENT_B): $(LIB)
	$(CC) $(CFLAGS) -o $(CLIENT_B) $(CLB_SRCS) $(LIB)

$(LIB):
	make -C libft/

clean:
	make clean -C libft/

fclean: clean
	rm -f $(SERVER)
	rm -f $(CLIENT)
	rm -f $(SERVER_B)
	rm -f $(CLIENT_B)
	make fclean -C libft/

re: fclean all

re_b: fclean bonus
