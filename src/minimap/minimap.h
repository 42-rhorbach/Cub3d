/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 14:27:29 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/30 11:28:19 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "types.h"

# include "libft.h"

# define MINIMAP_BACKGROUND 0x2A2A2AFF

# define MINIMAP_WALL 0x8E8E8EFF

# define MINIMAP_RAY 0xC83232FF

# define MINIMAP_SCALE 15

void	draw_minimap_ray(t_data *data, double end_x, double end_y);

void	draw_minimap(t_data *data);

typedef struct s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	mlx_image_t	*image;
}	t_line;

#endif
