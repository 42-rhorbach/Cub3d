/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:29:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/03/24 01:04:03 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "minimap.h"
#include "utils.h"
#include <math.h>

void	ft_put_pixel(mlx_image_t *image, int x, int y, int *rgb)
{
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	mlx_put_pixel(image, x, y, colour);
	//need to change colours to uint8_t for fsanitize
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
	ray->end_x = ray->wall_dist * fabs(cos(ray->dir_angle * PI / 180)); //for texture and minimap
	ray->end_y = ray->wall_dist * fabs(sin(ray->dir_angle * PI / 180)); //for texture and minimap
	ray->end_x = data->px + (ray->end_x * ray->x_dir); //for texture and minimap
	ray->end_y = data->py + (ray->end_y * ray->y_dir); //for texture and minimap
	ray->wall_dist *= sin(ray->ray_angle * PI / 180);
	// printf("%f\n", ray->wall_dist);
	if (ray->wall_dist > 1)
		ray->height = (int)(HEIGHT / ray->wall_dist);
	else
		ray->height = HEIGHT;
	min_y =(int)(-ray->height / 2 + HEIGHT / 2);
	if (min_y < 0)
		min_y = 0;
	max_y = (int)(ray->height / 2 + HEIGHT / 2);
	if (max_y >= HEIGHT)
		max_y = HEIGHT - 1;
	if (ray->last == 0 && ray->x_dir == 1)
		ray->c = CEAST;
	else if (ray->last == 0 && ray->x_dir == -1)
		ray->c = CWEST;
	else if (ray->last == 1 && ray->y_dir == 1)
		ray->c = CSOUTH;
	else if (ray->last == 1 && ray->y_dir == -1)
		ray->c = CNORTH;
	else
		ray->c = WHITE;
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

static void	ft_set_ray_data(t_rays *ray)
{
	direction_xy(ray->dir_angle, &ray->x_dir, &ray->y_dir);
	ray->x = (int)ray->end_x;
	ray->y = (int)ray->end_y;
	if (fabs(ray->dir_angle - 90) > A_MARGIN \
		&& fabs(ray->dir_angle - 270) > A_MARGIN)
		ray->dx = fabs(1 / cos(ray->dir_angle * PI / 180));
	else
		ray->dx = fabs(1 / cos((90 - A_MARGIN) * PI / 180)) + 1;
	if (fabs(ray->dir_angle - 180) > A_MARGIN && ray->dir_angle > A_MARGIN \
		&& fabs(ray->dir_angle - 360) > A_MARGIN)
		ray->dy = fabs(1 / sin(ray->dir_angle * PI / 180));
	else
		ray->dy = fabs(1 / sin(A_MARGIN * PI / 180)) + 1;
	if (ray->x_dir == 1)
		ray->sx = (1 - fmod(ray->end_x, 1)) * ray->dx;
	else
		ray->sx = fmod(ray->end_x , 1) * ray->dx;
	if (ray->y_dir == 1)
		ray->sy = (1 - fmod(ray->end_y, 1)) * ray->dy;
	else
		ray->sy = fmod(ray->end_y, 1) * ray->dy;
	return ;
}

static void	ft_ray_cast(t_rays *ray, t_data *data)
{
	while (true)
	{
		if (ray->sx < ray->sy)
		{
			ray->sx += ray->dx;
			ray->x += ray->x_dir;
			ray->last = 0;
		}
		else
		{
			ray->sy += ray->dy;
			ray->y += ray->y_dir;
			ray->last = 1;
		}
		if (ray->x <= 0 || ray->x > data->width - 1 \
			|| ray->y <= 0 || ray->y > data->height - 1)
			break ;
		else if (data->map[ray->y][ray->x] != '0')
			break ;
	}
	return ;
}

static void	ft_ray_calc(double d_angle, t_data *data, int x, double r_angle)
{
	t_rays	ray;

	ray.dir_angle = d_angle;
	ray.ray_angle = r_angle;
	ray.end_x = data->px;
	ray.end_y = data->py;
	ft_set_ray_data(&ray);
	ft_ray_cast(&ray, data);
	ft_draw_ray(&ray, data, x);
	draw_minimap_ray(data, ray.end_x, ray.end_y);
	return ;
}

void	ft_ray_loop(t_data *data)
{
	int		x;
	double	d_angle;
	double	r_angle;

	x = 0;
	d_angle = data->p_angle + HFOV;
	if (d_angle > 360)
		d_angle -= 360;
	r_angle = 180 - (90 + HFOV);
	while (x < WIDTH)
	{
		ft_ray_calc(d_angle, data, x, r_angle);
		r_angle += FOV_STEP;
		d_angle -= FOV_STEP;
	 	if (d_angle <= 0)
	 		d_angle = 360;
		x++;
	}
	return ;
}
