/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 12:37:29 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/07 18:57:13 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"


void n_angle_calc(double *angle)
{
	if (*angle > 90 && *angle < 180)
		*angle = 180 - *angle;
	else if (*angle > 180 && *angle < 270)
		*angle -= 180;
	else if (*angle > 270 && *angle < 360)
		*angle = 360 - *angle;
}

void direction_xy(double ray_angle, int *x_dir, int *y_dir)
{
	if ((ray_angle < 90 + A_MARGIN && ray_angle > 90 - A_MARGIN) \
		|| (ray_angle < 270 + A_MARGIN && ray_angle > 270 - A_MARGIN))
		*x_dir = 0;
	else if (ray_angle > 90 && ray_angle < 270)
		*x_dir = -1;
	else
		*x_dir = 1;
	if ((ray_angle < 180 + A_MARGIN && ray_angle > 180 - A_MARGIN) \
		|| (ray_angle < 0 + A_MARGIN && ray_angle > 0 - A_MARGIN) \
		|| (ray_angle < 360 + A_MARGIN && ray_angle > 360 - A_MARGIN))
		*y_dir = 0;
	else if (ray_angle > 180 && ray_angle < 360)
		*y_dir = 1;
	else
		*y_dir = -1;
}
