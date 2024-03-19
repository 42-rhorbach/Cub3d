# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvorstma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 14:17:08 by jvorstma          #+#    #+#              #
#    Updated: 2024/01/18 14:58:00 by jvorstma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Wextra -Werror -D SL_TEX='"$(dir $(realpath $(lastword $(MAKEFILE_LIST))))/textures/"'
RM= rm -r

##########

NAME= cub3D

##########

LIBFT= ./Libft/libft.a
LIBFLAGS= -L$(dir $(LIBFT)) -lft -L$(dir $(MLX42)) -lmlx42 -ldl

ifeq ($(shell uname),Linux)
LIBFLAGS += -lglfw -lm
else
LIBFLAGS += -lglfw3 -framework Cocoa -framework OpenGl -framework IOKit -lm
endif

ifdef DEBUG
CFLAGS += -g
endif

##########

MLX42_DIR= ./MLX42
MLX42_BUILD_DIR= build
MLX42= $(MLX42_DIR)/$(MLX42_BUILD_DIR)/libmlx42.a

##########

HEADERS= ./Libft/libft.h \
		./MLX42/include/MLX42/MLX42.h \
		./src/types.h \
		./src/error.h \
		./src/utils.h \
		./src/parse/parser.h \
		./src/init_game/game.h \
		./src/raycasting/raycast.h

##########

SDIR= src/
SOURCE= main.c \
		error.c \
		utils.c \
		parse/parse_info.c \
		parse/parse_utils.c \
		parse/parse_map.c \
		parse/validate_map.c \
		parse/validate_path.c \
		parse/validate_colour.c \
		init_game/init_mlx.c \
		raycasting/raycast.c

##########

INCLUDES= $(addprefix -I, $(sort $(dir $(HEADERS))))

##########

ODIR= obj
OBJECTS= $(addprefix $(ODIR)/,$(SOURCE:.c=.o))

##########

clear_line= \e[K
move_up= \e[A
define prettycomp
printf "$(1)$(clear_line)\n"
$(1)
printf "$(move_up)"
endef

##########

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFLAGS) -o $@

$(LIBFT):
	@git submodule update --init --recursive $(dir $(LIBFT))
	@$(MAKE) -sC $(dir $(LIBFT))

$(MLX42):
	@git submodule update --init --recursive $(dir $(MLX42_DIR))
	@cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/$(MLX42_BUILD_DIR)
	@$(MAKE) -sC $(MLX42_DIR)/$(MLX42_BUILD_DIR) -j4

$(ODIR)/%.o: $(SDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(call prettycomp,$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@)

clean:
	@if [ -d "$(ODIR)" ]; then \
		$(RM) $(ODIR); \
	fi
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean: clean
	@if [ -x "$(NAME)" ]; then \
		$(RM) $(NAME); \
	fi
	@$(MAKE) -C $(dir $(LIBFT)) fclean
	$(RM) -f $(MLX42_DIR)/$(MLX42_BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re

## we need to recompile changes in the headerfiles aswell, without doing make re
