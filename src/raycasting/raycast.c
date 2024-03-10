/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/03/10 23:12:27 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "utils.h"
#include "types.h"
#include <math.h>

static void	ft_put_pixel(mlx_image_t *image, int j, int i, int *rgb)
{
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 125;
	mlx_put_pixel(image, j, i, colour);
}

static void	ft_draw_ray(t_rays *ray, t_data *data, int x)
{
	int		y;
	float	height;
	float	wall_dst;
	int		min_y;
	int		max_y;

	if (ray->x_dir == -1)
		ray->x += ray->dx;
	if (ray->y_dir == -1)
		ray->y += ray->dy;
	if (ray->y_dir == 0)
		ray->y = data->py;
	if (ray->x_dir == 0)
		ray->x = data->px;
	//we need to find a way to do this correctly.
	//wall dist are correct depending on the dir, so our solution
	//could be in handeling this the correct way.
	wall_dst = sqrt(pow(data->px - ray->x, 2) + pow(data->py - ray->y, 2));
	if (x * FOV_STEP < FOV / 2)
		height = wall_dst * sin((60+ (x * FOV_STEP)) * PI / 180);
	else if (x * FOV_STEP > FOV / 2)
		height = wall_dst * sin((120 - (x * FOV_STEP)) * PI / 180);
	else
		height = wall_dst;
	printf("%f\n", height);
	height = (HEIGHT / height); //add/change scaling
	min_y =(int)(-height / 2 + HEIGHT / 2);
	while (min_y < 0)
		min_y = 0;
	max_y = (int)(height / 2 + HEIGHT / 2);
	while (max_y >= HEIGHT)
		max_y = HEIGHT - 1;
	y = 0;
	ray->c = 0xFFFF0044;
	while (y < HEIGHT && y >= 0 && x >= 0 && x < WIDTH)
	{
		if (y < min_y)
			ft_put_pixel(data->image[4], x, y, data->ceiling);
		else if (y >= min_y && y <= max_y)
			mlx_put_pixel(data->image[4], x, y, ray->c);
		else if (y > max_y)
			ft_put_pixel(data->image[4], x, y, data->floor);
		y++;
	}
}

static void	ft_new_xy(t_rays *ray, double angle)
{
	ray->dx = fmod(ray->x, 1);
	ray->dy = fmod(ray->y, 1);
	if (ray->x_dir == 1)
		ray->dx = 1 - ray->dx;
	if (ray->y_dir == 1)
		ray->dy = 1 - ray->dy;
	if (ray->dx < MARGIN)
		ray->dx = 1;
	if (ray->dy < MARGIN)
		ray->dy = 1;
	if (ray->x_dir != 0 && ray->y_dir != 0)
	{
		if (ray->dx / cos(angle * PI / 180) < ray->dy / sin(angle * PI / 180))
		{
			ray->dy = ray->dx * tan(angle * PI / 180);
			ray->last = 1;
		}
		else
		{
			ray->dx = (ray->dy / tan(angle * PI / 180));
			ray->last = 0;
		}
	}
	else if (ray->x_dir == 0)
		ray->last = 0;
	else
		ray->last = 1;
	ray->x += (ray->dx * ray->x_dir);
	ray->y += (ray->dy * ray->y_dir);
	ray->end_x = (int)ray->x;
	ray->end_y = (int)ray->y;
}

static void	ft_ray_cast(double angle, t_rays *ray, t_data *data)
{
	ray->x = data->px;
	ray->y = data->py;
	ray->end_x = (int)data->px;
	ray->end_y = (int)data->py;
	n_angle_calc(&angle);
	while (ray->end_x >= 1 && ray->end_x < data->width - 1 \
			&& ray->end_y >= 1 && ray->end_y < data->height - 1 \
			&& data->map[ray->end_y][ray->end_x] == '0')
		ft_new_xy(ray, angle);
}

static void	ft_ray_calc(double ray_angle, t_data *data, int x)
{
	t_rays	ray;

	direction_xy(ray_angle, &ray.x_dir, &ray.y_dir);
	ft_ray_cast(ray_angle, &ray, data);
	ft_draw_ray(&ray, data, x);
}

t_error	ft_ray_loop(t_data *data)
{
	int		x;
	double	ray_angle;

	x = 0;
	ray_angle = data->p_angle + (FOV / 2);
	if (ray_angle > 360)
		ray_angle -= 360;
	while (x < WIDTH)
	{
		ft_ray_calc(ray_angle, data, x);
		ray_angle -= FOV_STEP;
	 	if (ray_angle < A_MARGIN)
	 		ray_angle = 360;
		x++;
	}
	return (OK);
}
