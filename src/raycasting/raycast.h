/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:35:23 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/03/20 18:06:59 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "error.h"
# include "types.h"

void	ft_put_pixel(mlx_image_t *image, int x, int y, int *rgb);

void	ft_ray_loop(t_data *data);

#endif
