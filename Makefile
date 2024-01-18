# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvorstma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 14:17:08 by jvorstma          #+#    #+#              #
#    Updated: 2024/01/18 14:48:44 by jvorstma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Wextra -Werror
RM= rm -r

##########

NAME= cub3D

##########

LIBFT_DIR= ./libft
LIBFT= ./libft/libft.a
LIBFLAGS= -L$(dir $(LIBFT)) -lft -L$(dir $(MLX42)) -lmlx42

ifeq ($(shell uname),Linux)
LIBFLAGS += -lglfw
else
LIBFLAGS += -lglfw3 -framework Cocoa -framework OpenGl -framework IOKit
endif

##########

MLX42_DIR= ./MLX42
MLX42_BUILD_DIR= build
MLX42= $(MLX42_DIR)/$(MLX42_BUILD_DIR)/libmlx42.a

##########

HEADERS= ./libft/libft.h \
	./MLX42/include/MLX42/MLX42.h \

##########

SOURCE= main.c \

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

$(NAME): $(OBJECTS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBFLAGS) -o $@

$(LIBFIT):
	@git submodule update --init --recursive $(dir $(LIBFT))
	 @$(MAKE) -C $(dir $(LIBFT))

$(MLX42):
	@git submodule update --init --recursive $(dir $(MLX42_DIR))
	 cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/$(MLX42_BUILD_DIR)
	 $(MAKE) -C $(MLX42_DIR)/$(MLX42_BUILD_DIR) -j4

$(ODIR):
	@mkdir -p $(ODIR)

$(ODIR)/%.o: %.c $(HEADER) | $(ODIR)
	@$(call prettycomp,$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@)

clean:
	@if [ -d "$(ODIR)" ]; then \
		$(RM) $(ODIR); \
	fi
	@$(MAKE) C $(LIBFT) clean

fclean: clean
	@if [ -x "$(NAME)" ]; then \
		$(RM) $(NAME); \
	fi
	@$(MAKE) -C $(LIBFT) fclean
	$(RM) -f $(MLX42_DIR)/$(MLX42_BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re
