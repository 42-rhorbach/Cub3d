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

# include <stdio.h> //for printf testing

# define HEIGHT 2024
# define WIDTH 2024

# define CELL_SIZE 100

# define STEP_X 4
# define STEP_Y 4

# define ANGLE 90

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
	E_TEXTURE_EXTENSION,
	E_MAP_NOT_CLOSED,
	E_INCORRECT_ELEMENT,
	E_WRONG_QUANTITY,
	E_INV_INSTRC,
	E_INCORRECT_COLOUR,
	E_ELEMENT_MISSING,
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
	mlx_image_t	*images;
	char		**map;
	int			width;
	int			height;
	char		face;
	int			px;
	int			py;
	int			ceiling[3];
	int			c;
	int			floor[3];
	int			f;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}	t_data;

#endif