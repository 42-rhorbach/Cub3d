/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/03/22 12:59:46 by jvorstma      ########   odam.nl         */
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
	int		min_y;
	int		max_y;

	if (ray->last == 0)
		ray->wall_dist = ray->sx - ray->dx;
	else
		ray->wall_dist = ray->sy - ray->dy;
	// printf("%f\t", ray->wall_dist);
	if (fabs(ray->ray_angle - 90) > A_MARGIN)
		ray->wall_dist *= sin(ray->ray_angle * PI / 180);
	if (ray->wall_dist != 0)
		ray->height = (int)(HEIGHT / ray->wall_dist);
	else
		ray->height = HEIGHT;
	// printf("%f, %i\n", ray->wall_dist, ray->height);
	min_y =(int)(-ray->height / 2 + HEIGHT / 2);
	if (min_y < 0)
		min_y = 0;
	max_y = (int)(ray->height / 2 + HEIGHT / 2);
	if (max_y >= HEIGHT)
		max_y = HEIGHT - 1;
	ray->c = 0x00FFFF66;
	y = 0;
	while (y < HEIGHT - 1 && y >= 0 && x >= 0 && x < WIDTH - 1)
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
	return ;
}

static void	ft_set_ray_data(t_rays *ray, t_data *data)
{
	direction_xy(ray->dir_angle, &ray->x_dir, &ray->y_dir);
	ray->end_x = (int)data->px;
	ray->end_y = (int)data->py;
	ray->dx = fabs(1 / cos(ray->dir_angle * PI / 180));
	ray->dy = fabs(1 / sin(ray->dir_angle * PI / 180));
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

static void	ft_ray_cast(t_rays *ray, t_data *data)
{
	// while (true)
	while (ray->end_x >= 0 && ray->end_x < data->width \
			&& ray->end_y >= 0 && ray->end_y < data->height \
			&& data->map[ray->end_y][ray->end_x] == '0')
	{
		if (ray->x_dir != 0 && ray->y_dir != 0)
			ft_new_xy(ray);
		else if (ray->x_dir == 0)
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
		// if (ray->end_x < 1 || ray->end_x >= data->width - 1 \
		// 	|| ray->end_y < 1 || ray->end_y >= data->height - 1)
		// 	break ;
		// else if (data->map[ray->end_y][ray->end_x] != '0')
		// 	break ;
	}
	return ;
}

static void	ft_ray_calc(double d_angle, t_data *data, int x, double r_angle)
{
	t_rays	ray;

	ray.dir_angle = d_angle;
	ray.ray_angle = r_angle;
	ft_set_ray_data(&ray, data);
	ft_ray_cast(&ray, data);
	ft_draw_ray(&ray, data, x);
	return ;
}

t_error	ft_ray_loop(t_data *data)
{
	int		x;
	double	d_angle;
	double	r_angle;

	x = 0;
	d_angle = data->p_angle + HFOV;
	if (d_angle > 360)
		d_angle -= 360;
	r_angle = 90 + HFOV;
	while (x < WIDTH)
	{
		ft_ray_calc(d_angle, data, x, r_angle);
		r_angle -= FOV_STEP;
		d_angle -= FOV_STEP;
	 	if (d_angle <= 0)
	 		d_angle = 360;
		x++;
	}
	return (OK);
}
