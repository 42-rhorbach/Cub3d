/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/11 10:30:29 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <math.h>

// static void	ft_cursor_hook(double xpos, double ypos, void *param)
// {
// 	(void)param;
// 	printf("xpos: %f, ypos: %f\n", xpos, ypos);
// }

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

static t_error ft_init_window(t_data *data)
{
	data->window = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->window \
		|| mlx_image_to_window(data->mlx, data->window, 0, 0) == -1)
	{
		mlx_close_window(data->mlx); // TODO: This shouldn't have to be called here; refactor main() so it automatically happens, if it doesn't already
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
	// mlx_cursor_hook(data->mlx, &ft_cursor_hook, NULL);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (OK);
}