/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/11 10:53:04 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/15 00:40:01 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "error.h"
# include "types.h"
# include "utils.h"
# include "raycast.h"

typedef struct s_move
{
	double	dy;
	double	dx;
	double	step;
	int		dir_x;
	int		dir_y;
	double	new_x;
	double	new_y;
}	t_move;

t_error	ft_init_game(t_data *data);
void	ft_game_loop(void *param);

#endif
