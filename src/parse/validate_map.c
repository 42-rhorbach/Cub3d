/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:16:05 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/01 17:37:22 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static t_error	ft_enclosed_grid(char **map, int x, int y)
{
	printf("%c\n", map[y][x]);
	return (OK);
}

t_error	ft_validate_map(t_data *data)
{
	if (ft_enclosed_grid(data->map_grid, data->px, data->py) != OK)
		return (get_error());
	return (OK);
}
