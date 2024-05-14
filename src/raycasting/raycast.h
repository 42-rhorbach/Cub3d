/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:35:23 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/14 13:19:51 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "error.h"
# include "types.h"
# include "utils.h"
# include <math.h>

typedef struct s_wall_pixel
{
	int		min_y;
	int		max_y;
	t_side	side;
	double	real_height;
	double	height_percent;
	double	width_percent;
	size_t	wall_y;
	size_t	wall_x;
	size_t	offset;

}	t_wall_pixel;

void	ft_ray_loop(t_data *data);
void	ft_draw_ray(t_rays *ray, t_data *data, int x);

#endif
