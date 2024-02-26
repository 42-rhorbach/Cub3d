/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:06:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/26 23:03:05 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "../raycasting/raycast.h"

// static void	ft_get_dxy(t_data *data, int dir, int *dy, int *dx)
// {
// 	if (dir == 'u')
// 	{
		
// 	}
// 	else if (dir == 'd')
// 	{

// 	}
// 	else if (dir == 'l')
// 	{

// 	}
// 	else if (dir == 'r')
// 	{

// 	}
// 	else
// 		return (0);
// 	return (1)
// }

static void	move_player(t_data *data, int dx, int dy)
{
	//int	dy;
	//int	dx;

// we need the ft_get_dxy function to see which direction we are going,
//depening on our current angle, we then know how much we need to add or substract from x and y
//we do need to use some trigonometry for that part, if we are not i a stract clean angle.

	//if (!ft_get_dxy(data, direction, &dy, &dx))
	//	return ;
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

static void	ft_move_angle(t_data *data, int angle_change)
{
	data->fov += angle_change;
	if (data->fov <= 0)
		data->fov = 360 - data->fov;
	else if (data->fov < 360)
		data->fov -= 360;
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
		ft_move_angle(data, ANGLE_STEP);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ft_move_angle(data, -ANGLE_STEP);
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
