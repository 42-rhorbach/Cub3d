/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/26 12:19:23 by jvorstma      ########   odam.nl         */
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

static void	move_player(t_data *data, int dx, int dy)
{
	if ((data->py + dy) / CELL_SIZE < 0 || (data->py + dy) / CELL_SIZE >= data->height)
		return ;
	if ((data->px + dx) / CELL_SIZE < 0 || (data->px + dx) / CELL_SIZE >= data->width)
		return ;
	if (data->map[(data->py + dy) / CELL_SIZE][(data->px + dx) / CELL_SIZE] != '0')
		return ;
	data->px += dx;
	data->py += dy;
	if (ft_ray_loop(data) != OK)
		mlx_close_window(data->mlx);
}

static void	move_fov(t_data *data, int angle_change)
{
	data->fov += angle_change;
	if (ft_ray_loop(data) != OK)
		mlx_close_window(data->mlx);
}

static void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(data, 0, -STEP_Y);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(data, 0, STEP_Y);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(data, -STEP_X, 0);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(data, STEP_X, 0);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_fov(data, -ANGLE_STEP);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_fov(data, ANGLE_STEP);
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
	if (ft_ray_loop(*data) != OK)
	{
		mlx_close_window((*data)->mlx);
		return (get_error());
	}
	mlx_key_hook((*data)->mlx, &ft_hook, *data);
	mlx_loop((*data)->mlx);
	mlx_terminate((*data)->mlx);
	return (OK);
}
