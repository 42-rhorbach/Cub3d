/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/26 12:00:30 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

//need to know which side it hit the wall, for the textures.
static void	ft_draw_ray(t_rays *ray, t_data *data, int x)
{
	int		y;
	int		min_y;
	int		max_y;
	uint32_t	c;

	y = (int)HEIGHT / sqrt(pow(data->px - (ray->end_x * CELL_SIZE), 2) + pow(data->py - (ray->end_y * CELL_SIZE), 2));
	c = 0xF00000FF;
	min_y = -y / 2 + HEIGHT / 2;
	if (min_y < 0)
		min_y = 0;
	max_y = y / 2 + HEIGHT / 2;
	if (max_y >= HEIGHT)
		max_y = HEIGHT - 1;
	while (min_y >= 0 && max_y >= 0 && max_y < HEIGHT && min_y < max_y)
	{
		mlx_put_pixel(data->image, x, min_y, c);
		min_y++;
	}
}

static void	ft_straight_ray(t_data *data, t_rays *ray, int dir_x, int dir_y)
{
	ray->x_dir = dir_x;
	ray->y_dir = dir_y;
	ray->dx = dir_x;
	ray->dy = dir_y;
	ray->end_x = (int)(data->px / CELL_SIZE);
	ray->end_y = (int)(data->py / CELL_SIZE);
	ray->x = data->px;
	ray->y = data->py;
	while (ray->end_x >= 0 && ray->end_x < data->width \
			&& ray->end_y >= 0 && ray->end_y < data->height \
			&& data->map[ray->end_y][ray->end_x] == '0')
	{
		ray->x += ray->x_dir;
		ray->y += ray->y_dir;
		ray->end_x = (int)((data->px - ray->x) / CELL_SIZE);
		ray->end_x = (int)((data->py - ray->y) / CELL_SIZE);
	}
}

static void	ft_new_xy(t_rays *ray, double angle)
{
	ray->dx = ray->x - (ray->end_x * CELL_SIZE);
	ray->dy = ray->y - (ray->end_y * CELL_SIZE);
	if (ray->x_dir == 1)
		ray->dx = CELL_SIZE - ray->dx;
	if (ray->y_dir == 1)
		ray->dy = CELL_SIZE - ray->dy;
	if (ray->dy < MARGE)
		ray->dy = CELL_SIZE;
	if (ray->dx < MARGE)
		ray->dx = CELL_SIZE;
	if (ray->dx / cos(angle * PI / 180) <= ray->dy / sin(angle * PI / 180))
	{
		ray->x += ray->dx * ray->x_dir;
		ray->y += (ray->dx * tan(angle * PI / 180)) * ray->y_dir;
	}
	else
	{
		ray->y += ray->dy * ray->y_dir;
		ray->x += (ray->dy / tan(angle * PI / 180)) * ray->x_dir;
	}
	ray->end_x = (int)(ray->x / CELL_SIZE);
	ray->end_y = (int)(ray->y / CELL_SIZE);
}

static void	ft_ray_cast(double angle, t_rays *ray, t_data *data)
{
	if (angle > 270)
		angle = 360 - angle;
	if (angle > 180)
		angle -= 180;
	if (angle > 90)
		angle = 180 - angle;
	ray->x = data->px;
	ray->y = data->py;
	ray->end_x = (int)(data->px / CELL_SIZE);
	ray->end_y = (int)(data->py / CELL_SIZE);
	while (ray->end_x >= 0 && ray->end_x < data->width \
			&& ray->end_y >= 0 && ray->end_y < data->height \
			&& data->map[ray->end_y][ray->end_x] == '0')
		ft_new_xy(ray, angle);
}

static void	ft_ray_calc(double angle, t_data *data, int x)
{
	t_rays	ray;

	if (fabs(angle - 90.0) < MARGE)
		ft_straight_ray(data, &ray, 0, -1);
	else if (fabs(angle - 180.0) < MARGE)
		ft_straight_ray(data, &ray, -1, 0);
	else if (fabs(angle - 270.0) < MARGE)
		ft_straight_ray(data, &ray, 0, 1);
	else if (fabs(angle - 360.0) < MARGE || angle < MARGE)
		ft_straight_ray(data, &ray, 1, 0);
	else
	{
		if (angle > 90 && angle < 270)
			ray.x_dir = -1;
		else
			ray.x_dir = 1;
		if (angle > 180 && angle < 360)
			ray.y_dir = 1;
		else
			ray.y_dir = -1;
		ft_ray_cast(angle, &ray, data);
	}
	ft_draw_ray(&ray, data, x);
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
	step = ANGLE / (WIDTH - 1);
	while (x < WIDTH)
	{
		ft_ray_calc(angle, data, x);
	 	angle -= step;
	 	if (angle <= 0.0)
	 		angle += 360;
		x++;
	}
	return (OK);
}
