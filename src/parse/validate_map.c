/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:16:05 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/05 23:06:36 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static t_error	ft_validate_spot(char **map, int i, int j)
{
	if ((i - 1) < 0 || (j - 1) < 0 \
		|| (j + 1) >= (int)ft_strlen(map[i - 1]) \
		|| (j + 1) >= (int)ft_strlen(map[i + 1]) \
		|| map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' ' \
		|| map[i - 1][j + 1] == ' ' || map[i][j - 1] == ' ' \
		|| map[i][j + 1] == ' ' || map[i + 1][j - 1] == ' ' \
		|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
		return (set_error(E_MAP_NOT_CLOSED));
	return (OK);
}

t_error	ft_validate_map(t_data *data)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	while (data->map && i < data->height)
	{
		j = 0;
		width = ft_strlen(data->map[i]);
		while (j < width)
		{
			if (data->map[i][j] == '0' || data->map[i][j] == data->face)
			{
				if ((i + 1) >= data->height || (j + 1) >= width)
					return (set_error(E_MAP_NOT_CLOSED));
				if (ft_validate_spot(data->map, i, j) != OK)
					return (get_error());
			}
			else if (data->map[i][j] != ' ' && data->map[i][j] != '1')
				return (set_error(E_INCORRECT_ELEMENT));
			j++;
		}
		i++;
	}
	return (OK);
}
