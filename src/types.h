/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 16:14:48 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/01/18 16:14:49 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "MLX42.h"
# include <unistd.h>

typedef enum e_error
{
	OK,
	E_ARGC,
	E_MLX,
	E_SYS,
	E_CALLOC,
	E_NO_MAP,
	E_EMPTY_ARG,
	E_EXTENSION,
	E_MAP_NOT_CLOSED,
	E_INCORRECT_ELEMENT,
	E_WRONG_QUANTITY,
	E_INV_INSTRC,
}	t_error;

typedef enum e_texture_index
{
	EXIT,
	FLOOR,
	HATCH,
	PLAYER,
	SHINY,
	WALL,
	TEXTURE_COUNT
}	t_texture_index;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*images[TEXTURE_COUNT];
	char		**map_grid;
	size_t		width;
	size_t		height;
	int			px;
	int			py;
}	t_data;

#endif
