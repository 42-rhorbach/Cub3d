/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 16:57:37 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/14 00:37:35 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
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
	if ((int)(data->py + dy) < 1 || (int)(data->py + dy) >= data->height - 1)
		return ;
	if ((int)(data->px + dx) < 1 || (int)(data->px + dx) >= data->width - 1)
		return ;
	if (data->map[(int)(data->py + dy)][(int)(data->px + dx)] != '0')
		return ;
	if (data->map[(int)(data->py + dy - 1)][(int)(data->px + dx)] != '0' \
		&& data->map[(int)(data->py + dy)][(int)(data->px + dx - 1)] != '0')
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
