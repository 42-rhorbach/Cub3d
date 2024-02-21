/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/21 14:14:34 by jvorstma      ########   odam.nl         */
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
	printf("%i, %i, %i\n", y, end_x, end_y);
	while (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT / 2)
	{
	//	mlx_put_pixel(data->image, x, HEIGHT - y, 0xFF0000FF);
	//	mlx_put_pixel(data->image, x, y, 0x0F0000FF);
		y++;
	}
}

static void	ft_new_xy(t_rays *rays, double angle)
{
	double	step_x;
	double	step_y;

	if (angle > 270)
		angle -= angle;
	else if (angle > 180)
		angle = 180 - (angle - 180);
	else if (angle > 90)
		angle = 90 - (angle - 90);
	step_x = fmod(rays->x, CELL_SIZE);
	step_y = fmod(rays->y, CELL_SIZE);
	if (step_x == 0)
		step_x = CELL_SIZE;
	if (step_y == 0)
		step_y = CELL_SIZE;
	if (rays->x_dir == 1)
		step_x = CELL_SIZE - step_x;
	if (rays->y_dir == 1)
		step_y = CELL_SIZE - step_y;
	if (step_x < step_y)
		step_y = step_x / tan(angle * PI / 180);
	else
		step_x = step_y * tan(angle * PI / 180);
	rays->x += step_x * rays->x_dir;
	rays->y += step_y * rays->y_dir;
}

static void	ft_ray_cast(double angle, t_rays rays, t_data *data, int x)
{
	int	y;

	rays.x = data->px;
	rays.y = data->py;
	rays.end_x = (int)(rays.x / CELL_SIZE);
	rays.end_y = (int)(rays.y / CELL_SIZE);
	while (rays.end_x >= 0 && rays.end_x < data->width \
			&& rays.end_y >= 0 && rays.end_y < data->height \
			&& data->map[rays.end_y][rays.end_x] == '0')
	{
		ft_new_xy(&rays, angle);
		rays.end_x = (int)(rays.x / CELL_SIZE);
		rays.end_y = (int)(rays.y / CELL_SIZE);
	}
//	if (rays.end_x < 0 || rays.end_x >= data->width || rays.end_y < 0 || rays.end_y >= data->height)	
//		printf("%i, %i, %i\n", rays.end_x, rays.end_y, x);
	y = (int)sqrt(pow(data->px - rays.x, 2) + pow(data->py - rays.y, 2));
//	printf("y: %i, end_x: %i, end_y: %i\n", y, rays.end_x, rays.end_y);
	while (x >= 0 && x < WIDTH && y >= 0 && y <= HEIGHT / 2)
	{
	//	mlx_put_pixel(data->image, x, y, 0xFF0000FF);
	//	mlx_put_pixel(data->image, x, HEIGHT - y, 0xFF0000FF);
		y++;
	}
}

static void	ft_ray_calc(double angle, t_data *data, int x)
{
	t_rays	rays;

	if ((int)angle == 90)
		ft_straight_ray(data, x, 0, -1);
	else if ((int)angle == 180)
		ft_straight_ray(data, x, -1, 0);
	else if ((int)angle == 270)
		ft_straight_ray(data, x, 0, 1);
	else if ((int)angle == 360 || (int)angle == 0)
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
	angle = data->fov + (ANGLE / 2);
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

//working with doubles, checking a int  is not possible.
//find work around