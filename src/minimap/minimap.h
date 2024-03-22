/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 14:27:29 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/22 15:37:26 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "types.h"

# include "libft.h"

# define MINIMAP_BACKGROUND_R 42
# define MINIMAP_BACKGROUND_G 42
# define MINIMAP_BACKGROUND_B 42

# define MINIMAP_WALL_R 242
# define MINIMAP_WALL_G 242
# define MINIMAP_WALL_B 242

# define MINIMAP_RAY_R 200
# define MINIMAP_RAY_G 50
# define MINIMAP_RAY_B 50

# define MINIMAP_SCALE 20

void	draw_minimap_ray(t_data *data, double end_x, double end_y);

void	draw_minimap(t_data *data);

struct s_line
{
	int x0;
	int y0;
	int x1;
	int y1;
	mlx_image_t *image;
};
typedef struct s_line t_line;

#endif
