/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 12:37:29 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/23 21:17:31 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <math.h>

void n_angle_calc(double *angle)
{
	if (*angle > 90 && *angle <= 180)
		*angle = 180 - *angle;
	else if (*angle > 180 && *angle <= 270)
		*angle -= 180;
	else if (*angle > 270 && *angle <= 360)
		*angle = 360 - *angle;
}

void direction_xy(double ray_angle, int *x_dir, int *y_dir)
{
	if (fabs(ray_angle - 90) < A_MARGIN || fabs(ray_angle - 270) < A_MARGIN) // TODO: Why does this not do the `|| ray_angle < A_MARGIN` seen below?
		*x_dir = 0; // TODO: Why isn't x_dir and y_dir a boolean? It seems strange that they can be 0, if they are about the four quadrants of a radian circle
	if (ray_angle > 90 && ray_angle < 270)
		*x_dir = -1; // left
	else
		*x_dir = 1; // right
	if (fabs(ray_angle - 180) < A_MARGIN \
		|| fabs(ray_angle - 360) < A_MARGIN || ray_angle < A_MARGIN)
		*y_dir = 0;
	if (ray_angle > 180 && ray_angle < 360)
		*y_dir = 1; // bottom
	else
		*y_dir = -1; // top
	//answers to TODO: questions:
	//x_dir = 0, if the angle is 90 of 270, we dont want to move on the x axis.
	//the movement will be straight in negative or positive y direction, and the x coordinate should stay the same. thats why it is set to 0.
	//the same goes for y_dir = 0, this should be the case if the angel is 180, 360 or 0.
	//0 and 360 are the same, if the angle==0 we set the angle to 360, but just in case we miss a specific case, we also check here if the angel is 0.
	//so in the radian circle we set x_dir or y_dir to 0 if the angle is on (or near) one of the 4 axis.
	
	//we could still look into the use of A_MARGIN, maybe it is a bit of a overkill, since we only need to now this when dividing by the cos or sin of the angle.
	//because we shouldn't divide by zero. but we could very well only check this before doing said division.
}
