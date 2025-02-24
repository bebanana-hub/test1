# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vincent <vincent@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 16:25:45 by vgalloni          #+#    #+#              #
#    Updated: 2025/02/24 15:21:17 by vincent          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = $(wildcard *.c) $(wildcard utils/**/*.c)
OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/, $(SRC:.c=.o))

LIB42_DIR = ./lib/lib42
LIB42_LIB = $(LIB42_DIR)/lib42.a

MLX_DIR = ./lib/mlx42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm

INCLUDES = -I $(MLX_DIR)/include -I $(LIB42_DIR)

all: libmlx fetch_lib $(NAME)

fetch_lib:
	@git submodule update --init --recursive

libmlx:
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)/utils/assets_man
	@mkdir -p $(OBJS_DIR)/utils/map_test
	@mkdir -p $(OBJS_DIR)/utils/err_man

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB42_LIB) $(MLX_FLAGS)


$(LIB42_LIB): $(LIB42_DIR)
	@make -C $(LIB42_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C $(LIB42_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB42_DIR)
	
re: fclean all