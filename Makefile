# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 20:54:25 by acastilh          #+#    #+#              #
#    Updated: 2024/04/04 01:07:56 by acastilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)
LIBS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -L/usr/lib -lXext -lX11 -lm -lz

SRC_DIR = src
INC_DIR = include
LIB_DIR = lib
LIBFT_DIR = $(LIB_DIR)/libft
MLX_DIR = $(LIB_DIR)/minilibx-linux
GNL_DIR = $(LIB_DIR)/get_next_line

SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(SRC_DIR)/parser/*.c) \
      $(wildcard $(SRC_DIR)/game/*.c) \
	  $(wildcard $(SRC_DIR)/graphics/*.c) \
	  $(wildcard $(SRC_DIR)/utils/*.c) \
      $(wildcard $(GNL_DIR)/*.c)
	  
OBJ = $(SRC:%.c=%.o)

all: libft mlx $(NAME)

test_minilibx: libft mlx
	$(CC) $(CFLAGS) -o test_minilibx test_minilibx.c $(LIBS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBS)

libft:
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all