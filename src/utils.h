/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 12:55:56 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/30 11:41:25 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	ft_put_pixel(mlx_image_t *image, int x, int y, uint8_t *rgb);
void	n_angle_calc(double *angle);
void	direction_xy(double ray_angle, int *x_dir, int *y_dir);

#endif
