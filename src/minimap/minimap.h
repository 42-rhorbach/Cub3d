/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 14:27:29 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/20 15:57:00 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "types.h"

# include "libft.h"

# define MINIMAP_BACKGROUND_R 37
# define MINIMAP_BACKGROUND_G 104
# define MINIMAP_BACKGROUND_B 190
# define MINIMAP_BACKGROUND_A 255

# define MINIMAP_WALL_R 190
# define MINIMAP_WALL_G 37
# define MINIMAP_WALL_B 181
# define MINIMAP_WALL_A 255

# define MINIMAP_SCALE 20

void	draw_minimap(t_data *data);

#endif
