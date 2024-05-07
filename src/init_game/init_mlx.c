/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/04/24 15:53:48 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "minimap.h"
#include "utils.h"
#include "../raycasting/raycast.h"
#include <math.h>

static void	ft_get_dxy(t_data *data, t_move_dir dir, double *dy, double *dx)
{
	double	n_angle;
	int		dir_x;
	int		dir_y;

	n_angle = data->p_angle;
	n_angle_calc(&n_angle);
	direction_xy(data->p_angle, &dir_x, &dir_y);
	*dx = cos(n_angle * PI / 180) * MOVE_STEP * dir_x;
	*dy = sin(n_angle * PI / 180) * MOVE_STEP * dir_y;
	if (dir == BACKWARD)
	{
		*dx = -*dx;
		*dy = -*dy;
	}
	else if (dir == LEFTWARD)
	{
		*dx = sin(n_angle * PI / 180) * MOVE_STEP * dir_y;
		*dy = -cos(n_angle * PI / 180) * MOVE_STEP * dir_x;
	}
	else if (dir == RIGHTWARD)
	{
		*dx = -sin(n_angle * PI / 180) * MOVE_STEP * dir_y;
		*dy = cos(n_angle * PI / 180) * MOVE_STEP * dir_x;
	}
}

static void	move_player(t_data *data, t_move_dir move_dir, double elapsed_time)
{
	double	dy;
	double	dx;

	ft_get_dxy(data, move_dir, &dy, &dx);
	dx *= elapsed_time;
	dy *= elapsed_time;
	if ((int)(data->py + dy) < 0 || (int)(data->py + dy) >= data->height)
		return ;
	if ((int)(data->px + dx) < 0 || (int)(data->px + dx) >= data->width)
		return ;
	if (data->map[(int)(data->py + dy)][(int)(data->px + dx)] != '0')
		return ;
	data->px += dx;
	data->py += dy;
}

static void	ft_move_angle(t_data *data, double angle_change)
{
	data->p_angle += angle_change;
	if (data->p_angle <= 0)
		data->p_angle += 360;
	else if (data->p_angle > 360)
		data->p_angle -= 360;
}

// static void	ft_cursor_hook(double xpos, double ypos, void *param)
// {
// 	(void)param;
// 	printf("xpos: %f, ypos: %f\n", xpos, ypos);
// }

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

void	ft_game_loop(void *param)
{
	t_data *const	data = param;
	double			time;
	double			elapsed_time;

	time = mlx_get_time();
	elapsed_time = time - data->time;
	data->time = time;
	if (data->inputs.forward)
		move_player(data, FORWARD, elapsed_time);
	if (data->inputs.backward)
		move_player(data, BACKWARD, elapsed_time);
	if (data->inputs.leftward)
		move_player(data, LEFTWARD, elapsed_time);
	if (data->inputs.rightward)
		move_player(data, RIGHTWARD, elapsed_time);
	if (data->inputs.counterclockwise)
		ft_move_angle(data, ROT_STEP * elapsed_time);
	if (data->inputs.clockwise)
		ft_move_angle(data, -ROT_STEP * elapsed_time);
	draw_minimap(data);
	ft_ray_loop(data);
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
	data->window = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->window \
		|| mlx_image_to_window(data->mlx, data->window, 0, 0) == -1)
	{
		mlx_close_window(data->mlx); // TODO: This shouldn't have to be called here; refactor main() so it automatically happens, if it doesn't already
		return (set_error(E_MLX));
	}
	data->minimap = mlx_new_image(data->mlx, data->width * MINIMAP_SCALE, \
					data->height * MINIMAP_SCALE);
	if (data->minimap == NULL)
	{
		mlx_close_window(data->mlx);
		return (set_error(E_MLX));
	}
	if (mlx_image_to_window(data->mlx, data->minimap, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return (set_error(E_MLX));
	}
	mlx_loop_hook(data->mlx, &ft_game_loop, data);
	mlx_key_hook(data->mlx, &ft_hook, data);
	// mlx_cursor_hook(data->mlx, &ft_cursor_hook, NULL);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (OK);
}
