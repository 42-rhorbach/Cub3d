/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:16:05 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/01 04:47:12 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"
#include "libft.h"

static t_error	ft_enclosed_grid(char **map, int x, int y)
{
	//check the map, how?
	return (OK);
}

t_error	ft_validate_map(t_parser *parse_info, t_data **data)
{
	int	i;

	(*data)->face = parse_info->face;
	(*data)->px = parse_info->px;
	(*data)->py = parse_info->py;
	if (ft_enclosed_grid(parse_info->map, parse_info->px, parse_info->py) != OK)
		return (set_error(E_MAP_NOT_CLOSED))
	i = 0;
	while (parse_info->map && parse_info->map[i])
	{
		(*data)->map_grid[i] = ft_strdup(parse_info->map[i]);
		if (!(*data)->map_grid[i])
			return (set_error(E_SYS));
	}
	(*data)->map_grid[i] = NULL;
	return (OK);
}
