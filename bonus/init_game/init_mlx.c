/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/18 12:40:22 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <math.h>

static t_error	load_texture(t_data *data, const char *texture_path,
								mlx_image_t **img)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(texture_path);
	if (texture == NULL)
		return (set_error(E_MLX));
	*img = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	if (*img == NULL)
		return (set_error(E_MLX));
	return (OK);
}

static void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W)
		data->inputs.forward = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_S)
		data->inputs.backward = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_A)
		data->inputs.leftward = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_D)
		data->inputs.rightward = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_LEFT)
		data->inputs.counterclockwise = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_RIGHT)
		data->inputs.clockwise = (keydata.action != MLX_RELEASE);
}

static t_error	ft_init_window(t_data *data)
{
	data->window = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->window \
		|| mlx_image_to_window(data->mlx, data->window, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return (set_error(E_MLX));
	}
	data->minimap = mlx_new_image(data->mlx, data->width * MINIMAP_SCALE, \
					data->height * MINIMAP_SCALE);
	if (!data->minimap \
		|| mlx_image_to_window(data->mlx, data->minimap, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return (set_error(E_MLX));
	}
	return (OK);
}

t_error	ft_init_game(t_data *data)
{
	if (WIDTH < 100 || HEIGHT < 100 || WIDTH > 3000 || HEIGHT > 2500)
		return (set_error(E_SCREEN));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (data->mlx == NULL)
		return (set_error(E_MLX));
	if (load_texture(data, data->north, &data->walls[NORTH]) != OK \
		|| load_texture(data, data->east, &data->walls[EAST]) != OK \
		|| load_texture(data, data->south, &data->walls[SOUTH]) != OK \
		|| load_texture(data, data->west, &data->walls[WEST]) != OK)
		return (get_error());
	if (ft_init_window(data) != OK)
		return (get_error());
	mlx_loop_hook(data->mlx, &ft_game_loop, data);
	mlx_key_hook(data->mlx, &ft_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (OK);
}
