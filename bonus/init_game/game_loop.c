/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 16:57:37 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/17 13:41:57 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <math.h>

static void	ft_get_dxy(t_move_dir dir, t_move *m, int dir_x_buf)
{
	if (dir == BACKWARD)
	{
		m->dir_x = -m->dir_x;
		m->dir_y = -m->dir_y;
	}
	else if (dir == LEFTWARD)
	{
		m->dir_x = m->dir_y;
		m->dir_y = -dir_x_buf;
	}
	else if (dir == RIGHTWARD)
	{
		m->dir_x = -m->dir_y;
		m->dir_y = dir_x_buf;
	}
	if (dir == RIGHTWARD || dir == LEFTWARD)
	{
		m->dx = sin(m->angle * PI / 180) * m->step * m->dir_x;
		m->dy = cos(m->angle * PI / 180) * m->step * m->dir_y;
	}
	else if (dir == FORWARD || dir == BACKWARD)
	{
		m->dx = cos(m->angle * PI / 180) * m->step * m->dir_x;
		m->dy = sin(m->angle * PI / 180) * m->step * m->dir_y;
	}
}

static void	move_player(t_data *data, t_move_dir move_dir, double elapsed_time)
{
	t_move	m;

	m.step = MOVE_STEP * elapsed_time;
	m.angle = data->p_angle;
	n_angle_calc(&m.angle);
	direction_xy(data->p_angle, &m.dir_x, &m.dir_y);
	ft_get_dxy(move_dir, &m, m.dir_x);
	m.new_x = data->px + m.dx;
	m.new_y = data->py + m.dy;
	if ((int)(m.new_y) < 1 || (int)(m.new_y) >= data->height - 1 \
		|| (int)(m.new_x) < 1 || (int)(m.new_x) >= data->width - 1)
		return ;
	if (data->map[(int)(m.new_y)][(int)(m.new_x)] != '0' \
		|| data->map[(int)(m.new_y + 0.05 * m.dir_y)][(int)(data->px)] != '0' \
		|| data->map[(int)(data->py)][(int)(m.new_x + 0.05 * m.dir_x)] != '0')
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
