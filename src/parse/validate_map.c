/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:16:05 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/17 10:04:41 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static t_error	ft_validate_spot(char **map, int i, int j, t_data *data)
{
	if ((i + 1) >= data->height || (j + 1) >= data->width \
		|| (i - 1) < 0 || (j - 1) < 0 \
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

	i = 0;
	while (data->map && i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (data->map[i][j] == '0' || data->map[i][j] == data->face)
			{
				if (ft_validate_spot(data->map, i, j, data) != OK)
					return (get_error());
				if (data->map[i][j] == data->face)
					data->map[i][j] = '0';
			}
			else if (data->map[i][j] != ' ' && data->map[i][j] != '1')
				return (set_error(E_INCORRECT_ELEMENT));
			j++;
		}
		i++;
	}
	return (OK);
}
