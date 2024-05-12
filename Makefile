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
CFLAGS= -Wall -Wextra -Werror -D SL_TEX='"$(dir $(realpath $(lastword $(MAKEFILE_LIST))))/textures/"' -Ofast -march=native
RM= rm -r

##########

NAME= cub3D
BNAME= cub3D_bonus

##########

LIBFT= ./Libft/libft.a
LIBFLAGS= -L$(dir $(LIBFT)) -lft -L$(dir $(MLX42)) -lmlx42 -ldl

ifeq ($(shell uname),Linux)
LIBFLAGS += -lglfw -lm
else
LIBFLAGS += -lglfw3 -framework Cocoa -framework OpenGl -framework IOKit -lm
endif

ifdef DEBUG
CFLAGS += -g -fsanitize=address,undefined
endif

##########

MLX42_DIR= ./MLX42
MLX42_BUILD_DIR= build
MLX42= $(MLX42_DIR)/$(MLX42_BUILD_DIR)/libmlx42.a

##########

SDIR= src/

HEADERS= ./Libft/libft.h \
		./MLX42/include/MLX42/MLX42.h \
		$(SDIR)init_game/game.h \
		$(SDIR)parse/parser.h \
		$(SDIR)raycasting/raycast.h \
		$(SDIR)error.h \
		$(SDIR)types.h \
		$(SDIR)utils.h


SOURCE= init_game/init_mlx.c \
		init_game/game_loop.c \
		parse/parse_info.c \
		parse/parse_map.c \
		parse/parse_utils.c \
		parse/validate_colour.c \
		parse/validate_map.c \
		parse/validate_path.c \
		raycasting/raycast.c \
		error.c \
		main.c \
		utils.c

##########

BDIR= bonus/

BHEADERS= ./Libft/libft.h \
		./MLX42/include/MLX42/MLX42.h \
		$(BDIR)init_game/game.h \
		$(BDIR)parse/parser.h \
		$(BDIR)raycasting/raycast.h \
		$(BDIR)error.h \
		$(BDIR)types.h \
		$(BDIR)utils.h \
 		$(BDIR)minimap.h

BSOURCE= init_game/init_mlx.c \
		init_game/game_loop.c \
		parse/parse_info.c \
		parse/parse_map.c \
		parse/parse_utils.c \
		parse/validate_colour.c \
		parse/validate_map.c \
		parse/validate_path.c \
		raycasting/raycast.c \
		error.c \
		utils.c \
		main.c \
		minimap/minimap.c

##########

INCLUDES= $(addprefix -I, $(sort $(dir $(HEADERS))))
BINCLUDES= $(addprefix -I, $(sort $(dir $(BHEADERS))))

##########

ODIR= obj
OBJECTS= $(addprefix $(ODIR)/,$(SOURCE:.c=.o))

BODIR= bobj
BOBJECTS= $(addprefix $(BODIR)/,$(BSOURCE:.c=.o))

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

bonus: $(BNAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFLAGS) -o $@

$(BNAME): $(LIBFT) $(MLX42) $(BOBJECTS)
	$(CC) $(CFLAGS) $(BINCLUDES) $(BOBJECTS) $(LIBFLAGS) -o $@

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

$(BODIR)/%.o: $(BDIR)/%.c $(BHEADERS)
	@mkdir -p $(dir $@)
	@$(call prettycomp,$(CC) -c $(CFLAGS) $(BINCLUDES) $< -o $@)

clean:
	@if [ -d "$(ODIR)" ]; then \
		$(RM) $(ODIR); \
	fi
	@if [ -d "$(BODIR)" ]; then \
		$(RM) $(BODIR); \
	fi
	@$(MAKE) -sC $(dir $(LIBFT)) clean

fclean: clean
	@if [ -x "$(NAME)" ]; then \
		$(RM) $(NAME); \
	fi
	@if [ -x "$(BNAME)" ]; then \
		$(RM) $(BNAME); \
	fi
	@$(MAKE) -sC $(dir $(LIBFT)) fclean
	@$(RM) -f $(MLX42_DIR)/$(MLX42_BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
