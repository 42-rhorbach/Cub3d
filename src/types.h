/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 16:14:48 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/02/09 13:31:57 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "MLX42.h"

typedef enum e_error
{
	OK,
	E_ARGC,
	E_MLX,
	E_SYS,
	E_NO_MAP,
	E_EXTENSION,
	E_MAP_NOT_CLOSED,
	E_INCORRECT_ELEMENT,
	E_WRONG_QUANTITY,
}	t_error;

typedef enum e_texture_index
{
	FLOOR,
	PLAYER,
	NORTH_WALL,
	SOUTH_WALL,
	EAST_WALL,
	WEST_WALL,
	TEXTURE_COUNT
}	t_texture_index;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*images[TEXTURE_COUNT];
	char		**map_grid;	//
	size_t		width;	//width window
	size_t		height; //height window
	int			px; //player x pos
	int			py;	//player y pos
	//int			move_count;
}	t_data;

#endif
