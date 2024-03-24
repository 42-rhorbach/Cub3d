/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 14:27:11 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/23 22:27:11 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minimap.h"
#include "raycast.h"
#include <stdlib.h>

static void draw_minimap_line(t_line l)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int error;
	int e2;

    dx = abs(l.x1 - l.x0);
	sx = -1;
	if (l.x0 < l.x1)
		sx = 1;
    dy = -abs(l.y1 - l.y0);
	sy = -1;
	if (l.y0 < l.y1)
		sy = 1;
    error = dx + dy;
    while (true)
	{
		ft_put_pixel(l.image, l.x0, l.y0,
			(int [3]){MINIMAP_RAY_R, MINIMAP_RAY_G, MINIMAP_RAY_B});
        if (l.x0 == l.x1 && l.y0 == l.y1)
			return ;
        e2 = 2 * error;
        if (e2 >= dy)
		{
            if (l.x0 == l.x1)
				return ;
            error = error + dy;
            l.x0 = l.x0 + sx;
		}
        if (e2 <= dx)
		{
            if (l.y0 == l.y1)
				return ;
            error = error + dx;
            l.y0 = l.y0 + sy;
		}
	}
}

static int	get_scaled(double n, int size)
{
	int minimap_size;

	minimap_size = size * MINIMAP_SCALE;
	return ((int)(n / size * minimap_size));
}

void	draw_minimap_ray(t_data *data, double end_x, double end_y)
{
	if (end_x < 0 || end_x > data->width - 1 || end_y < 0 || end_y > data->height -1)
		return ;
	draw_minimap_line((t_line){
		get_scaled(data->px, data->width),
		get_scaled(data->py, data->height),
		get_scaled(end_x, data->width),
		get_scaled(end_y, data->height),
		data->minimap});
}

static void	draw_tile_pixel(mlx_image_t *minimap, char tile, int x, int y)
{
	if (tile == '0')
	{
		ft_put_pixel(minimap, x, y, (int [3]){
			MINIMAP_BACKGROUND_R,
			MINIMAP_BACKGROUND_G,
			MINIMAP_BACKGROUND_B});
	}
	else if (tile == '1')
	{
		ft_put_pixel(minimap, x, y, (int [3]){
			MINIMAP_WALL_R,
			MINIMAP_WALL_G,
			MINIMAP_WALL_B});
	}
}

static void	draw_minimap_pixel(t_data *data, char tile, size_t tile_x, \
	size_t tile_y)
{
	size_t	pixel_y;
	size_t	pixel_x;
	size_t	y;
	size_t	x;

	pixel_y = 0;
	while (pixel_y < MINIMAP_SCALE)
	{
		pixel_x = 0;
		while (pixel_x < MINIMAP_SCALE)
		{
			y = tile_y * MINIMAP_SCALE + pixel_y;
			x = tile_x * MINIMAP_SCALE + pixel_x;
			draw_tile_pixel(data->minimap, tile, x, y);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_minimap(t_data *data)
{
	size_t	tile_y;
	size_t	tile_x;
	char	tile;

	tile_y = 0;
	while (tile_y < (size_t)data->height)
	{
		tile_x = 0;
		while (tile_x < (size_t)data->width)
		{
			tile = data->map[tile_y][tile_x];
			draw_minimap_pixel(data, tile, tile_x, tile_y);
			tile_x++;
		}
		tile_y++;
	}
}
