/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 14:27:11 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/20 16:20:36 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minimap.h"

static void	draw_tile_pixel(uint8_t *pixels, char tile, size_t color_index)
{
	if (tile == '0')
	{
		pixels[color_index + 0] = MINIMAP_BACKGROUND_R;
		pixels[color_index + 1] = MINIMAP_BACKGROUND_G;
		pixels[color_index + 2] = MINIMAP_BACKGROUND_B;
		pixels[color_index + 3] = MINIMAP_BACKGROUND_A;
	}
	else if (tile == '1')
	{
		pixels[color_index + 0] = MINIMAP_WALL_R;
		pixels[color_index + 1] = MINIMAP_WALL_G;
		pixels[color_index + 2] = MINIMAP_WALL_B;
		pixels[color_index + 3] = MINIMAP_WALL_A;
	}
}

static size_t	get_index(size_t x, size_t y, size_t width)
{
	return (x + y * width);
}

static void	draw_minimap_pixel(t_data *data, char tile, size_t tile_x,
			size_t tile_y)
{
	size_t	pixel_y;
	size_t	pixel_x;
	size_t	pixel_y_pos;
	size_t	pixel_x_pos;
	size_t	color_index;

	pixel_y = 0;
	while (pixel_y < MINIMAP_SCALE)
	{
		pixel_x = 0;
		while (pixel_x < MINIMAP_SCALE)
		{
			pixel_y_pos = tile_y * MINIMAP_SCALE + pixel_y;
			pixel_x_pos = tile_x * MINIMAP_SCALE + pixel_x;
			color_index = get_index(pixel_x_pos, pixel_y_pos,
					MINIMAP_SCALE * data->width) * 4;
			draw_tile_pixel(data->minimap->pixels, tile, color_index);
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
