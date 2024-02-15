/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/15 15:20:23 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

static void	ft_new_x_y(int *new_x, int *new_y, double rad)
{
	if ((1 / sin(rad)) < (1 / cos(rad)))
	{
		*new_y += 1;
		*new_x = (int)((*new_y) / tan(rad));
	}
	else
	{
		*new_x += 1;
		*new_y = (int)(*new_x * tan(rad));
	}
}

static t_error	ft_ray_cast_calc(t_data *data, double rad)
{
	int	start_x;
	int	start_y;

	start_x = data->px;
	start_y = data->py;
	while ((start_y / CELL_SIZE) < data->height && (start_x / CELL_SIZE) < data->width \
			&& data->map[(start_y / CELL_SIZE)][(start_x / CELL_SIZE)] != 1)
	{
		ft_new_x_y(&start_x, &start_y, rad);
		mlx_put_pixel(data->image, start_x, start_y, 0xFFF0FFFF);
	}
	return (OK);
}

t_error	ft_ray_loop(t_data *data)
{
	int	x;
	double angle;

	x = 0;
	angle = data->fov - 30;
	if (angle < 0)
		angle = 360 - angle;
	while (x < WIDTH && angle < 90 && angle > 0)
	{
		if (ft_ray_cast_calc(data, angle * PI / 180) != OK)
			return (get_error());
		angle += (ANGLE / (double)WIDTH);
		x++;
	}
	return (OK);
}