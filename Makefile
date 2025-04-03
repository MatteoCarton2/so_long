# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 10:52:39 by mcarton           #+#    #+#              #
#    Updated: 2025/04/01 11:52:57 by mcarton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

# MiniLibX
MLX_DIR = mlx/minilibx_opengl_20191021
MLX_FLAGS = -framework OpenGL -framework AppKit
MLX_LIB = -L$(MLX_DIR) -lmlx

SRCS = srcs/main.c \
       srcs/map_load.c \
	   srcs/map_check.c \
       srcs/path.c \
       srcs/game_init.c \
       srcs/game_events.c \
	   srcs/utils.c

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make clean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
