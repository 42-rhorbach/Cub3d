/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/18 19:15:05 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

static void	ft_straight_ray(t_data *data, int x, int x_dir, int y_dir)
{
	int		y;
	int		end_x;
	int		end_y;
	double	dx;
	double	dy;

	end_x = (int)(data->px / CELL_SIZE);
	end_y = (int)(data->py / CELL_SIZE);
	dx = 0;
	dy = 0;
	while (end_x >= 0 && end_x < WIDTH \
			&& end_y >= 0 && end_y < HEIGHT \
			&& data->map[end_y][end_x] == '0')
	{
		dx += 1 * x_dir;
		dy += 1 * y_dir;
		end_x = (int)((data->px + dx) / CELL_SIZE);
		end_y = (int)((data->py + dy) / CELL_SIZE);
	}
	y = (int)sqrt(pow(dx, 2) + pow(dy, 2));
	while (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT / 2)
	{
		mlx_put_pixel(data->image, x, HEIGHT - y, 0xFF0000FF);
		mlx_put_pixel(data->image, x, y, 0x0F0000FF);
		y++;
	}
}

static void	ft_new_xy(t_rays *rays, double angle)
{
	double	x_step;
	double	y_step;
	
	x_step = CELL_SIZE - fmod(rays->x, CELL_SIZE);
	y_step = CELL_SIZE - fmod(rays->y, CELL_SIZE);
	if (x_step / cos(angle) < y_step / sin(angle))
	{
		rays->x += x_step * rays->x_dir;
		rays->y += x_step * tan(angle) * rays->y_dir;
	}
	else
	{
		rays->y += y_step * rays->y_dir;
		rays->x += y_step / tan(angle) * rays->y_dir;
	}
}

static void	ft_ray_cast(double angle, t_rays rays, t_data *data, int x)
{
	int	y;

	angle = angle * PI / 180;
	rays.x = data->px;
	rays.y = data->py;
	rays.end_x = (int)(rays.x / CELL_SIZE);
	rays.end_y = (int)(rays.y / CELL_SIZE);
	while (rays.end_x >= 0 && rays.end_x < WIDTH \
			&& rays.end_y >= 0 && rays.end_y < HEIGHT \
			&& data->map[rays.end_y][rays.end_x] == '0')
	{
		ft_new_xy(&rays, angle);
		rays.end_x = (int)(rays.x / CELL_SIZE);
		rays.end_y = (int)(rays.y / CELL_SIZE);
	}
	y = (int)sqrt(pow(data->px - rays.x, 2) + pow(data->py - rays.y, 2));
	while (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT / 2)
	{
		mlx_put_pixel(data->image, x, HEIGHT - y, 0x0F0000FF);
		mlx_put_pixel(data->image, x, y, 0x00F000FF);
		y++;
	}
}

static void	ft_ray_calc(double angle, t_data *data, int x)
{
	t_rays	rays;

	if (angle == 90)
		ft_straight_ray(data, x, 0, -1);
	else if (angle == 180)
		ft_straight_ray(data, x, -1, 0);
	else if (angle == 270)
		ft_straight_ray(data, x, 0, 1);
	else if (angle == 360 || angle == 0)
		ft_straight_ray(data, x, 1, 0);
	else
	{
		if (angle > 90 && angle < 270)
			rays.x_dir = -1;
		else
			rays.x_dir = 1;
		if (angle > 180 && angle < 360)
			rays.y_dir = 1;
		else
			rays.y_dir = -1;
		ft_ray_cast(angle, rays, data, x);
	}
}

t_error	ft_ray_loop(t_data *data)
{
	int		x;
	double	angle;
	double	step;

	x = 0;
	angle = data->fov + ANGLE / 2;
	if (angle > 360)
		angle -= 360;
	step = ANGLE / WIDTH;
	while (x < WIDTH)
	{
		ft_ray_calc(angle, data, x);
		angle -= step;
		if (angle <= 0)
			angle += 360;
		x++;;
	}
	return (OK);
}