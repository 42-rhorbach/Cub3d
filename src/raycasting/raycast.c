/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/03/22 01:16:44 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "utils.h"
#include <math.h>

static void	ft_put_pixel(mlx_image_t *image, int j, int i, int *rgb)
{
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 125;
	mlx_put_pixel(image, j, i, colour);
	return ;
}

static void	ft_draw_ray(t_rays *ray, t_data *data, int x)
{
	int		y;
	float	wall_dist;
	int		height;
	int		min_y;
	int		max_y;

	if (ray->last == 0)
		wall_dist = ray->sx - ray->dx;
	else
		wall_dist = ray->sy - ray->dy;
	height = (int)(HEIGHT / wall_dist);
	min_y =(int)(-height / 2 + HEIGHT / 2);
	if (min_y < 0)
		min_y = 0;
	max_y = (int)(height / 2 + HEIGHT / 2);
	if (max_y >= HEIGHT)
		max_y = HEIGHT - 1;
	ray->c = 0x00FFFF66;
	y = 0;
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
	return ;
}

static void	ft_new_xy(t_rays *ray)
{
	if (ray->x_dir != 0 && ray->y_dir != 0)
	{
		if (ray->sx < ray->sy)
		{
			ray->sx += ray->dx;
			ray->end_x += ray->x_dir;
			ray->last = 0;
		}
		else
		{
			ray->sy += ray->dy;
			ray->end_y += ray->y_dir;
			ray->last = 1;
		}
	}
	else
	{
		if (ray->x_dir == 0)
		{
			ray->sy += ray->dy;
			ray->end_y += ray->y_dir;
			ray->last = 1;
		}
		else
		{
			ray->sx += ray->dx;
			ray->end_x += ray->x_dir;
			ray->last = 0;
		}
	}
	return ;
}

static void	ft_get_sxy(t_rays *ray, t_data *data)
{
	ray->sx = fmod(data->px, 1);
	ray->sy = fmod(data->py, 1);
	if (ray->x_dir == 1)
		ray->sx = 1 - ray->sx;
	if (ray->y_dir == 1)
		ray->sy = 1 - ray->sy;
	ray->sx *= ray->dx;
	ray->sy *= ray->dy;
	return ;
}

static void	ft_get_dxy(t_rays *ray, double angle)
{
	ray->dx = fabs(1 / cos(angle * PI / 180));
	ray->dy = fabs(1 / sin(angle * PI / 180));
	return ;
}

static void	ft_ray_cast(t_rays *ray, t_data *data, double angle)
{
	ray->end_x = (int)data->px;
	ray->end_y = (int)data->py;
	ft_get_dxy(ray, angle);
	ft_get_sxy(ray, data);
	while (ray->end_x >= 0 && ray->end_x < data->width \
			&& ray->end_y >= 0 && ray->end_y < data->height \
			&& data->map[ray->end_y][ray->end_x] == '0')
		ft_new_xy(ray);	
	return ;
}

static void	ft_ray_calc(double dir_angle, t_data *data, int x)
{
	t_rays	ray;
	
	// double testx;
	// double testy;
	// testx = fabs(1 / (1 + 0 * (2 * x / (double)WIDTH - 1)));
	// testy = fabs(1 / (0 + 0.66 * (2 * x / (double)WIDTH - 1)));
	// printf("%f, %f\t", testx, testy);

	direction_xy(dir_angle, &ray.x_dir, &ray.y_dir);
	ft_ray_cast(&ray, data, dir_angle);
	ft_draw_ray(&ray, data, x);
	return ;
}

t_error	ft_ray_loop(t_data *data)
{
	int		x;
	double	dir_angle;

	x = 0;
	dir_angle = data->p_angle + HFOV;
	if (dir_angle > 360)
		dir_angle -= 360;
	while (x < WIDTH)
	{
		ft_ray_calc(dir_angle, data, x);
		dir_angle -= FOV_STEP;
	 	if (dir_angle <= 0)
	 		dir_angle = 360;
		x++;
	}
	return (OK);
}
