/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 12:37:29 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/19 15:46:13 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <math.h>

void n_angle_calc(double *angle)
{
	if (fabs(*angle - 90) < A_MARGIN)
		*angle = 90;
	else if (fabs(*angle - 180) < A_MARGIN)
		*angle = 0;
	else if (fabs(*angle - 270) < A_MARGIN)
		*angle = 90;
	else if (fabs(*angle - 360) < A_MARGIN || *angle < A_MARGIN)
		*angle = 0;
	else if (*angle > 90 && *angle < 180)
		*angle = 180 - *angle;
	else if (*angle > 180 && *angle < 270)
		*angle -= 180;
	else if (*angle > 270 && *angle < 360)
		*angle = 360 - *angle;
}

void direction_xy(double ray_angle, int *x_dir, int *y_dir)
{
	// if (fabs(ray_angle - 90) < A_MARGIN || fabs(ray_angle - 270) < A_MARGIN) // TODO: Why does this not do the `|| ray_angle < A_MARGIN` seen below?
	// 	*x_dir = 0; // TODO: Why isn't x_dir and y_dir a boolean? It seems strange that they can be 0, if they are about the four quadrants of a radian circle
	if (ray_angle > 90 && ray_angle < 270)
		*x_dir = -1; // left
	else
		*x_dir = 1; // right
	// if (fabs(ray_angle - 180) < A_MARGIN \
	// 	|| fabs(ray_angle - 360) < A_MARGIN || ray_angle < A_MARGIN)
	// 	*y_dir = 0;
	if (ray_angle > 180 && ray_angle < 360)
		*y_dir = 1; // bottom
	else
		*y_dir = -1; // top
}
