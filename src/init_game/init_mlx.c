/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/12 03:20:58 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	ft_put_pixel(mlx_image_t *images, int i, int j, int *rgb)
{
	int			k;
	int			l;
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	k = 0;
	while (k < 100)
	{
		l = 0;
		while (l < 100)
		{
			mlx_put_pixel(images, j * 100 + l, i * 100 + k, colour);
			l++;
		}
		k++;
	}
}

static void	ft_close_key(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

static void	ft_set_background(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (i < data->height / 2)
				ft_put_pixel(data->images, i, j, data->ceiling);
			else
				ft_put_pixel(data->images, i, j, data->floor);
			j++;
		}
		i++;
	}
}

t_error ft_init_game(t_data **data)
{
	(*data)->mlx = mlx_init((*data)->height * 110, (*data)->width * 110, "test", true);
	(*data)->images = mlx_new_image((*data)->mlx, (*data)->height * 100, (*data)->width * 100);
	mlx_image_to_window((*data)->mlx, (*data)->images, 10, 10);
	ft_set_background(*data);
	mlx_key_hook((*data)->mlx, &ft_close_key, *data);
	mlx_loop((*data)->mlx);
	mlx_terminate((*data)->mlx);
	return (OK);
}
