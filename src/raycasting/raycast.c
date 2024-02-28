/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/28 21:36:32 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

static void	ft_put_pixel(mlx_image_t *images, int j, int i, int *rgb)
{
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 125;
	mlx_put_pixel(images, j, i, colour);
}


//need to know which side it hit the wall, for the textures.
static void	ft_draw_ray(t_rays *ray, t_data *data, int x)
{
	int		y;
	int		min_y;
	int		max_y;

	y = (int)sqrt(pow((data->px - ray->x), 2) + pow((data->py - ray->y), 2));
	y = HEIGHT / y;
	min_y = -y / 2 + HEIGHT / 2;
	if (min_y < 0)
		min_y = 0;
	max_y = y / 2 + HEIGHT / 2;
	if (max_y >= HEIGHT)
		max_y = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < min_y)
			ft_put_pixel(data->image, x, y, data->ceiling);
		else if (y >= min_y && y <= max_y)
			mlx_put_pixel(data->image, x, y, ray->c);
		else if (y > max_y)
			ft_put_pixel(data->image, x, y, data->floor);
		y++;
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
	if (ray->dy < MARGIN)
		ray->dy = CELL_SIZE;
	if (ray->dx < MARGIN)
		ray->dx = CELL_SIZE;
	if (ray->dx / cos(angle * PI / 180) <= ray->dy / sin(angle * PI / 180))
	{
		ray->x += ray->dx * ray->x_dir;
		ray->y += (ray->dx * tan(angle * PI / 180)) * ray->y_dir;
		if (ray->x_dir == -1)
			ray->c = 0xFF0000FF;
		else
			ray->c = 0xFFFF00FF;
	}
	else
	{
		ray->y += ray->dy * ray->y_dir;
		ray->x += (ray->dy / tan(angle * PI / 180)) * ray->x_dir;
		if (ray->y_dir == -1)
			ray->c = 0x00FF00FF;
		else
			ray->c = 0x0000FFFF;
	}
	ray->end_x = (int)(ray->x / CELL_SIZE);
	ray->end_y = (int)(ray->y / CELL_SIZE);
}

static void	ft_ray_cast(double angle, t_rays *ray, t_data *data)
{
	printf("%f\n", angle);
	ray->x = data->px;
	ray->y = data->py;
	ray->end_x = (int)(data->px / CELL_SIZE);
	ray->end_y = (int)(data->py / CELL_SIZE);
	while (ray->end_x >= 0 && ray->end_x < data->width \
			&& ray->end_y >= 0 && ray->end_y < data->height \
			&& data->map[ray->end_y][ray->end_x] == '0')
		ft_new_xy(ray, angle);
}

static void	ft_ray_calc(double angle, t_data *data, int x, double ray_angle)
{
	t_rays	ray;

	if (fabs(angle - 90) < MARGIN || fabs(angle - 270) < MARGIN)
		ray.x_dir = 0;
	else if (angle > 90 && angle < 270)
		ray.x_dir = -1;
	else
		ray.x_dir = 1;
	if (fabs(angle - 360) < MARGIN || angle < MARGIN \
		|| fabs(angle - 180) < MARGIN)
		ray.y_dir = 0;
	else if (angle > 180 && angle < 360)
		ray.y_dir = 1;
	else
		ray.y_dir = -1;
	//lost in the angles. this is where it goes wrong.
	ft_ray_cast(ray_angle, &ray, data);
	ft_draw_ray(&ray, data, x);
}

t_error	ft_ray_loop(t_data *data)
{
	int		x;
	double	angle;
	double	step;
	double	ray_angle;

	x = 0;
	angle = data->fov + (ANGLE / 2);
	if (angle > 360)
		angle -= 360;
	step = ANGLE / (WIDTH -1);
	ray_angle = 60;
	while (x < WIDTH)
	{
		ft_ray_calc(angle, data, x, ray_angle);
		if (x < (WIDTH / 2))
			ray_angle += step;
		else
			ray_angle -= step;
		angle -= step;
	 	if (angle < MARGIN)
	 		angle += 360;
		x++;
	}
	return (OK);
}
