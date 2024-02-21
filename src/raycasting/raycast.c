/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/21 16:28:42 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

static void	ft_straight_ray(t_data *data, int *y, int x_dir, int y_dir)
{
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
	*y = (int)sqrt(pow(dx, 2) + pow(dy, 2));
}

static void	ft_new_xy(t_rays *rays, double angle)
{
	double	dx;
	double	dy;

	dx = rays->x - (rays->end_x * CELL_SIZE);
	dy = rays->y - (rays->end_y * CELL_SIZE);
	if (rays->x_dir == 1)
		dx = CELL_SIZE - dx;
	if (rays->y_dir == 1)
		dy = CELL_SIZE - dy;
	if (dy < 0.001)
		dy = CELL_SIZE;
	if (dx < 0.001)
		dx = CELL_SIZE;
	//printf("%i, %i, %f, %f, %f, %f", rays->end_x, rays->end_y, rays->x, rays->y, dx, dy);
	if (dx / cos(angle * PI / 180) <= dy / sin(angle * PI / 180))
	{
		rays->x += dx * rays->x_dir;
		rays->y += (dx * tan(angle * PI / 180)) * rays->y_dir;
	}
	else
	{
		rays->y += dy * rays->y_dir;
		rays->x += (dy / tan(angle * PI / 180)) * rays->x_dir;
	}
	rays->end_x = (int)(rays->x / CELL_SIZE);
	rays->end_y = (int)(rays->y / CELL_SIZE);
	//printf(" -> %f, %f, %i, %i\n", rays->x, rays->y, rays->end_x, rays->end_y);
}

static void	ft_ray_cast(double angle, t_rays rays, t_data *data, int *y)
{
	if (angle > 270)
		angle = 360 - angle;
	if (angle > 180)
		angle -= 180;
	if (angle > 90)
		angle = 180 - angle;
	rays.x = data->px;
	rays.y = data->py;
	rays.end_x = (int)(data->px / CELL_SIZE);
	rays.end_y = (int)(data->py / CELL_SIZE);
	while (rays.end_x >= 0 && rays.end_x < data->width \
			&& rays.end_y >= 0 && rays.end_y < data->height \
			&& data->map[rays.end_y][rays.end_x] == '0')
		ft_new_xy(&rays, angle);
	*y = (int)sqrt(pow(data->px - rays.x, 2) + pow(data->py - rays.y, 2));
}

static void	ft_ray_calc(double angle, t_data *data, int *y)
{
	t_rays	rays;
	double	marge;

	marge = 0.01;
	if (fabs(angle - 90.0) < marge)
		ft_straight_ray(data, y, 0, -1);
	else if (fabs(angle - 180.0) < marge)
		ft_straight_ray(data, y, -1, 0);
	else if (fabs(angle - 270.0) < marge)
		ft_straight_ray(data, y, 0, 1);
	else if (fabs(angle - 360.0) < marge || angle < marge)
		ft_straight_ray(data, y, 1, 0);
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
		ft_ray_cast(angle, rays, data, y);
	}
	//need to know which side it hit the wall, for the textures.
}

t_error	ft_ray_loop(t_data *data)
{
	int		x;
	int		y;
	double	angle;
	double	step;

	x = 0;
	angle = data->fov + (ANGLE / 2);
	if (angle > 360)
		angle -= 360;
	step = ANGLE / WIDTH;
	// ft_ray_calc(angle - step, data, x);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 2 * step, data, x + 1);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 3 * step, data, x + 2);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 4 * step, data, x + 3);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 5 * step, data, x + 4);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 6 * step, data, x + 5);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 7 * step, data, x + 6);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 8 * step, data, x + 7);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 9 * step, data, x + 8);
	// printf("----------------------------------------------------------\n");
	// ft_ray_calc(angle - 10 * step, data, x + 9);
	while (x < WIDTH)
	{
		ft_ray_calc(angle, data, &y);
		y *= (int)sqrt(pow(y, 2) - pow((x-WIDTH/2)/(WIDTH/2), 2));
		y = ((CELL_SIZE * HEIGHT)/y);
		printf("%i, %i\n", x, y);
	 	angle -= step;
	 	if (angle <= 0.0)
	 		angle += 360;
		x++;
	}
	return (OK);
}
