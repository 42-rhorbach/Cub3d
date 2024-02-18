/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/18 13:35:36 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "../raycasting/raycast.h"

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
				ft_put_pixel(data->image, j, i, data->ceiling);
			else
				ft_put_pixel(data->image, j, i, data->floor);
			j++;
		}
		i++;
	}
}

t_error ft_init_game(t_data **data)
{
	(*data)->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	(*data)->image = mlx_new_image((*data)->mlx, WIDTH, HEIGHT);
	if (!(*data)->image \
		|| mlx_image_to_window((*data)->mlx, (*data)->image, 0, 0) == -1)
	{
		mlx_close_window((*data)->mlx);
		return (set_error(E_MLX));
	}
	ft_set_background(*data);
	mlx_key_hook((*data)->mlx, &ft_close_key, *data);
	if (ft_ray_loop(*data) != OK)
	{
		mlx_close_window((*data)->mlx);
		return (get_error());
	}
	mlx_loop((*data)->mlx);
	mlx_terminate((*data)->mlx);
	return (OK);
}
