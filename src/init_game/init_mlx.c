/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/21 16:00:27 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	ft_put_pixel(mlx_image_t *images, int j, int i, int *rgb)
{
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 125;
	mlx_put_pixel(images, j, i, colour);
}

static void	move_player(t_data *data, int dx, int dy)
{
	const int	nx = data->px + dx;
	const int	ny = data->py + dy;

	if (data->map[ny / CELL_SIZE][nx / CELL_SIZE] == '1')
		return ;
	data->px = nx;
	data->py = ny;
	// data->images[PLAYER]->instances[0].x = data->px;
	// data->images[PLAYER]->instances[0].y = data->py;
}

static void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data *const	data = param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);
		if (keydata.key == MLX_KEY_W)
			move_player(data, 0, -STEP_Y);
		if (keydata.key == MLX_KEY_S)
			move_player(data, 0, STEP_Y);
		if (keydata.key == MLX_KEY_A)
			move_player(data, -STEP_X, 0);
		if (keydata.key == MLX_KEY_D)
			move_player(data, STEP_X, 0);
	}
}

static void	ft_set_background(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			if (j < HEIGHT / 2)
				ft_put_pixel(data->images, i, j, data->ceiling);
			else if (j < HEIGHT)
				ft_put_pixel(data->images, i, j, data->floor);
			i++;
		}
		j++;
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
	mlx_key_hook((*data)->mlx, &ft_hook, *data);
	mlx_loop((*data)->mlx);
	mlx_terminate((*data)->mlx);
	return (OK);
}
