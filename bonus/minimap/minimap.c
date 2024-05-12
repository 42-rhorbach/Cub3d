/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 14:27:11 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/05/07 23:23:12 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include <stdlib.h>

static void	minimap_draw_pixel(t_line l, t_bresh b)
{
	while (true)
	{
		mlx_put_pixel(l.image, l.x0, l.y0, MINIMAP_RAY);
		if (l.x0 == l.x1 && l.y0 == l.y1)
			return ;
		b.e2 = 2 * b.error;
		if (b.e2 >= b.dy)
		{
			if (l.x0 == l.x1)
				return ;
			b.error = b.error + b.dy;
			l.x0 = l.x0 + b.sx;
		}
		if (b.e2 <= b.dx)
		{
			if (l.y0 == l.y1)
				return ;
			b.error = b.error + b.dx;
			l.y0 = l.y0 + b.sy;
		}
	}
}

static void	draw_minimap_line(t_line l)
{
	t_bresh	b;

	b.dx = abs(l.x1 - l.x0);
	b.sx = -1;
	if (l.x0 < l.x1)
		b.sx = 1;
	b.dy = -abs(l.y1 - l.y0);
	b.sy = -1;
	if (l.y0 < l.y1)
		b.sy = 1;
	b.error = b.dx + b.dy;
	minimap_draw_pixel(l, b);
}

void	draw_minimap_ray(t_data *data, double end_x, double end_y)
{
	if (end_x < 0 || end_x > data->width - 1 || \
		end_y < 0 || end_y > data->height -1)
		return ;
	draw_minimap_line((t_line){
		(data->px * MINIMAP_SCALE),
		(data->py * MINIMAP_SCALE),
		(end_x * MINIMAP_SCALE),
		(end_y * MINIMAP_SCALE),
		data->minimap});
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
			if (tile == '0')
				mlx_put_pixel(data->minimap, (int)x, (int)y, \
								MINIMAP_BACKGROUND);
			else if (tile == '1')
				mlx_put_pixel(data->minimap, (int)x, (int)y, MINIMAP_WALL);
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
