/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/14 14:13:31 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	ft_put_pixel(mlx_image_t *images, int j, int i, int *rgb)
{
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 125;
	mlx_put_pixel(images, j, i, colour);
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
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i < HEIGHT / 2)
				ft_put_pixel(data->images, j, i, data->ceiling);
			else if (i < HEIGHT)
				ft_put_pixel(data->images, j, i, data->floor);
			j++;
		}
		i++;
	}
}

t_error ft_init_game(t_data **data)
{
	(*data)->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	(*data)->images = mlx_new_image((*data)->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window((*data)->mlx, (*data)->images, 0, 0) == -1)
	{
		mlx_close_window((*data)->mlx);
		return (set_error(E_MLX));
	}
	ft_set_background(*data);
	int	i = 0;
	while (i < 10)
	{
		int j = 0;
		while (j < 10)
		{
			mlx_put_pixel((*data)->images, (*data)->px + j, (*data)->py + i, 16);
			j++;
		}
		i++;
	}
	mlx_key_hook((*data)->mlx, &ft_close_key, *data);
	mlx_loop((*data)->mlx);
	mlx_terminate((*data)->mlx);
	return (OK);
}
