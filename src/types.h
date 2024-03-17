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

//for at codam
// # define HEIGHT 2064
// # define WIDTH 2064

// # define STEP_X 0.25
// # define STEP_Y 0.25

///////////////////////////////

//for my laptop at home
# define HEIGHT 480
# define WIDTH 640

# define STEP_X 0.25
# define STEP_Y 0.25

/////////////////////////////////
# define MARGIN 0.000001
# define A_MARGIN 1
# define FOV 60.00
# define HFOV FOV / 2
# define FOV_STEP FOV/(WIDTH - 1)
# define ROT_STEP 5
# define PI 3.14159265359

//for testing
// # define NORTH 0xFF0000FF //red
// # define SOUTH 0x0000FFFF //blue
// # define EAST 0x00FF00FF //green
// # define WEST 0xFFFF00FF //yellow
// # define WHITE 0xFFFFFFFF

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
	EAST,
	NORTH,
	SOUTH,
	WEST,
	TEXTURE_COUNT,
}	t_texture_index;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image[TEXTURE_COUNT+1];
	char		**map;
	int			width;
	int			height;
	char		face;
	double		p_angle;
	double		px;
	double		py;
	int			ceiling[3];
	int			c;
	int			floor[3];
	int			f;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}	t_data;

typedef struct s_rays
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		last;
	int		x_dir;
	int		y_dir;
	int		end_x;
	int		end_y;
	uint32_t	c;
}	t_rays;

#endif
