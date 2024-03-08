/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/03/08 19:00:18 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "utils.h"
#include <math.h>
#include "../raycasting/raycast.h"

static void	ft_get_dxy(t_data *data, int move_dir, float *dy, float *dx)
{
	double	n_angle;
	int		dir_x;
	int		dir_y;
	float	temp;

	n_angle = data->p_angle;
	n_angle_calc(&n_angle);
	direction_xy(data->p_angle, &dir_x, &dir_y);
	if (dir_x == 0)
		dir_x = 1;
	if (dir_y == 0)
		dir_y = 1;
	*dx = cos(n_angle * PI / 180) * STEP_X * dir_x;
	*dy = sin(n_angle * PI / 180) * STEP_Y * dir_y;
	if (move_dir == 's')
	{
		*dx = -*dx;
		*dy = -*dy;
	}
	else if (move_dir == 'a')
	{
		temp = *dx;
		*dx = *dy;
		*dy = -temp;
	}
	else if (move_dir == 'd')
	{
		temp = *dx;
		*dx = -*dy;
		*dy = temp;
	}
}

static void	move_player(t_data *data, int move_dir)
{
 	float	dy;
 	float	dx;

 	ft_get_dxy(data, move_dir, &dy, &dx);
	if ((int)(data->py + dy) < 0 + 1 || (int)(data->py + dy) >= data->height - 1)
		return ;
	if ((int)(data->px + dx) < 0 + 1 || (int)(data->px + dx) >= data->width - 1)
		return ;
	if (data->map[(int)(data->py + dy)][(int)(data->px + dx)] != '0')
		return ;
	printf("%f, %f\t", dx, dy);
	data->px += dx;
	data->py += dy;
	printf("%f, %f\n", data->px, data->py);
	if (ft_ray_loop(data) != OK)
		mlx_close_window(data->mlx);
}

static void	ft_move_angle(t_data *data, float angle_change)
{
	data->p_angle += angle_change;
	if (data->p_angle < A_MARGIN)
		data->p_angle += 360;
	else if (data->p_angle > 360)
		data->p_angle -= 360;
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
		move_player(data, 'w');
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(data, 's');
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(data, 'a');
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(data, 'd');
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		ft_move_angle(data, ROT_STEP);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ft_move_angle(data, -ROT_STEP);
}

// static t_error	load_texture(t_data *data, const char *texture_path,
// 								mlx_image_t **img)
// {
// 	mlx_texture_t	*texture;

// 	texture = mlx_load_png(texture_path);
// 	if (texture == NULL)
// 		return (set_error(E_MLX));
// 	*img = mlx_texture_to_image(data->mlx, texture);
// 	mlx_delete_texture(texture);
// 	if (*img == NULL)
// 		return (set_error(E_MLX));
// 	return (OK);
// }

t_error ft_init_game(t_data **data)
{
	printf("%f, %f\n", (*data)->px, (*data)->py);
	(*data)->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if ((*data)->mlx == NULL)
		return (set_error(E_MLX));
	/*if (load_texture((*data), (*data)->west, &(*data)->image[WEST]) != OK \
		|| load_texture((*data), (*data)->east, &(*data)->image[EAST]) != OK \
		|| load_texture((*data), (*data)->north, &(*data)->image[NORTH]) != OK \
		|| load_texture((*data), (*data)->south, &(*data)->image[SOUTH]) != OK)
	 	return (get_error());*/
	(*data)->image[4] = mlx_new_image((*data)->mlx, WIDTH, HEIGHT); //wat is dit?
	if (!(*data)->image[4] \
		|| mlx_image_to_window((*data)->mlx, (*data)->image[4], 0, 0) == -1)
	{
		mlx_close_window((*data)->mlx);
		return (set_error(E_MLX));
	}
	if (ft_ray_loop(*data) != OK)
	{
		mlx_close_window((*data)->mlx);
		mlx_terminate((*data)->mlx);
		return (get_error());
	}
	mlx_key_hook((*data)->mlx, &ft_hook, *data);
	mlx_loop((*data)->mlx);
	mlx_terminate((*data)->mlx);
	return (OK);
}
