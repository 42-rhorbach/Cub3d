/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 12:37:29 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/05/16 12:02:22 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <math.h>

void	ft_put_pixel(mlx_image_t *image, int x, int y, uint8_t *rgb)
{
	uint32_t	colour;

	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	mlx_put_pixel(image, x, y, colour);
}

void	n_angle_calc(double *angle)
{
	if (*angle > 90 && *angle <= 180)
		*angle = 180 - *angle;
	else if (*angle > 180 && *angle <= 270)
		*angle -= 180;
	else if (*angle > 270 && *angle <= 360)
		*angle = 360 - *angle;
}

void	direction_xy(double ray_angle, int *x_dir, int *y_dir)
{
	if (fabs(ray_angle - 90) < A_MARGIN || fabs(ray_angle - 270) < A_MARGIN)
		*x_dir = 0;
	else if (ray_angle > 90 && ray_angle < 270)
		*x_dir = -1;
	else
		*x_dir = 1;
	if (fabs(ray_angle - 180) < A_MARGIN \
		|| fabs(ray_angle - 360) < A_MARGIN || ray_angle < A_MARGIN)
		*y_dir = 0;
	else if (ray_angle > 180 && ray_angle < 360)
		*y_dir = 1;
	else
		*y_dir = -1;
}
