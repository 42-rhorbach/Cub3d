/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 14:27:29 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/29 13:47:45 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "types.h"

# include "libft.h"

# define MINIMAP_BACKGROUND ((int[3]){42, 42, 42})

# define MINIMAP_WALL ((int[3]){242, 242, 242})

# define MINIMAP_RAY ((int[3]){200, 50, 50})

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
