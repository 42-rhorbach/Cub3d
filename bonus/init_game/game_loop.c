/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 16:57:37 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/16 07:37:28 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <math.h>

static void	ft_get_dxy(t_data *data, t_move_dir dir, t_move *m)
{
	double	n_angle;

	n_angle = data->p_angle;
	n_angle_calc(&n_angle);
	direction_xy(data->p_angle, &m->dir_x, &m->dir_y);
	m->dx = cos(n_angle * PI / 180) * m->step * m->dir_x;
	m->dy = sin(n_angle * PI / 180) * m->step * m->dir_y;
	if (dir == BACKWARD)
	{
		m->dx = -m->dx;
		m->dy = -m->dy;
	}
	else if (dir == LEFTWARD)
	{
		m->dx = sin(n_angle * PI / 180) * m->step * m->dir_y;
		m->dy = -cos(n_angle * PI / 180) * m->step * m->dir_x;
	}
	else if (dir == RIGHTWARD)
	{
		m->dx = -sin(n_angle * PI / 180) * m->step * m->dir_y;
		m->dy = cos(n_angle * PI / 180) * m->step * m->dir_x;
	}
}

static void	move_player(t_data *data, t_move_dir move_dir, double elapsed_time)
{
	t_move	m;

	m.step = MOVE_STEP * elapsed_time;
	ft_get_dxy(data, move_dir, &m);
	m.new_x = data->px + m.dx;
	m.new_y = data->py + m.dy;
	if ((int)(m.new_y) < 1 || (int)(m.new_y) >= data->height - 1 \
		|| (int)(m.new_x) < 1 || (int)(m.new_x) >= data->width - 1)
		return ;
	if (data->map[(int)(m.new_y)][(int)(m.new_x)] != '0')
		return ;
	if (data->map[(int)(m.new_y + 0.05)][(int)(m.new_x + 0.05)] != '0' \
		|| data->map[(int)(m.new_y - 0.05)][(int)(m.new_x - 0.05)] != '0' \
		|| data->map[(int)(m.new_y - 0.05)][(int)(m.new_x)] != '0' \
		|| data->map[(int)(m.new_y - 0.05)][(int)(m.new_x + 0.05)] != '0' \
		|| data->map[(int)(m.new_y + 0.05)][(int)(m.new_x)] != '0' \
		|| data->map[(int)(m.new_y + 0.05)][(int)(m.new_x - 0.05)] != '0' \
		|| data->map[(int)(m.new_y)][(int)(m.new_x - 0.05)] != '0' \
		|| data->map[(int)(m.new_y)][(int)(m.new_x + 0.05)] != '0')
		return ;
	data->px = m.new_x;
	data->py = m.new_y;
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
