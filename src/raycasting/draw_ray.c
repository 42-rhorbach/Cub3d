/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 12:47:39 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/14 15:16:07 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static t_side	get_side(int last, int x_dir, int y_dir)
{
	if (last == 0 && x_dir == 1)
		return (EAST);
	else if (last == 0 && x_dir == -1)
		return (WEST);
	else if (last == 1 && y_dir == 1)
		return (NORTH);
	else
		return (SOUTH);
}

static uint32_t	get_wall_pixel(mlx_image_t *tex, t_wall_pixel *wp, int y)
{
	size_t		i;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	wp->height_percent = (wp->offset + y - wp->min_y) / wp->real_height;
	wp->wall_y = wp->height_percent * (tex->height - 1);
	i = (wp->wall_x + wp->wall_y * tex->width) * 4;
	r = (uint32_t)tex->pixels[i + 0] << 24;
	g = (uint32_t)tex->pixels[i + 1] << 16;
	b = (uint32_t)tex->pixels[i + 2] << 8;
	return (r | g | b | 255);
}

static void	ft_get_end_values(t_wall_pixel *wp, t_rays *ray, t_data *data, \
									mlx_image_t *tex)
{
	ray->end_x = ray->wall_dist * fabs(cos(ray->dir_angle * PI / 180));
	ray->end_y = ray->wall_dist * fabs(sin(ray->dir_angle * PI / 180));
	ray->end_x = data->px + (ray->end_x * ray->x_dir);
	ray->end_y = data->py + (ray->end_y * ray->y_dir);
	ray->wall_dist *= sin(ray->ray_angle * PI / 180);
	if (ray->wall_dist > 1)
		ray->height = (int)(HEIGHT / ray->wall_dist);
	else
		ray->height = HEIGHT;
	wp->min_y = (int)(-ray->height / 2 + HEIGHT / 2);
	if (wp->min_y < 0)
		wp->min_y = 0;
	wp->max_y = (int)(ray->height / 2 + HEIGHT / 2);
	if (wp->max_y >= HEIGHT)
		wp->max_y = HEIGHT - 1;
	if (wp->side == EAST || wp->side == WEST)
		wp->width_percent = fmod(ray->end_y, 1);
	else
		wp->width_percent = fmod(ray->end_x, 1);
	wp->real_height = (double)HEIGHT / ray->wall_dist;
	wp->offset = 0;
	if (wp->real_height > HEIGHT)
		wp->offset = (wp->real_height - HEIGHT) / 2;
	wp->wall_x = wp->width_percent * (tex->width - 1);
}

void	ft_draw_ray(t_rays *ray, t_data *data, int x)
{
	int				y;
	t_wall_pixel	wp;
	mlx_image_t		*tex;

	wp.side = get_side(ray->last, ray->x_dir, ray->y_dir);
	tex = data->walls[wp.side];
	if (wp.side == WEST || wp.side == EAST)
		ray->wall_dist = ray->sx - ray->dx;
	else
		ray->wall_dist = ray->sy - ray->dy;
	ft_get_end_values(&wp, ray, data, tex);
	y = 0;
	while (y < HEIGHT - 1 && y >= 0 && x >= 0 && x < WIDTH - 1)
	{
		if (y < wp.min_y)
			ft_put_pixel(data->window, x, y, data->ceiling);
		else if (y >= wp.min_y && y <= wp.max_y)
		{
			ray->c = get_wall_pixel(tex, &wp, y);
			mlx_put_pixel(data->window, x, y, ray->c);
		}
		else if (y > wp.max_y)
			ft_put_pixel(data->window, x, y, data->floor);
		y++;
	}
}
