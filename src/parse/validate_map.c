/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:16:05 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/01 10:12:29 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_error	ft_validate_map(t_data *data)
{
	int	i;
	int	j;
	int width;

	i = 0;
	while (data->map && i < data->height)
	{
		j = 0;
		width = ft_strlen(data->map[i]);
		while (j < width)
		{
			if (data->map[i][j] == '0' || data->map[i][j] == data->face)
			{
				if ((i - 1) < 0 || (i + 1) >= data->height \
					|| (j - 1) < 0 || (j + 1) >= width)
					return (set_error(E_MAP_NOT_CLOSED));
				if (data->map[i - 1][j - 1] == ' ' \
					|| data->map[i - 1][j] == ' ' \
					|| data->map[i - 1][j + 1] == ' ' \
					|| data->map[i][j - 1] == ' ' \
					|| data->map[i][j + 1] == ' ' \
					|| data->map[i + 1][j - 1] == ' ' \
					|| data->map[i + 1][j] == ' ' \
					|| data->map[i + 1][j + 1] == ' ')
					return (set_error(E_MAP_NOT_CLOSED));
			}
			else if (data->map[i][j] != ' ' && data->map[i][j] != '1')
			{
				printf("here\n");
				return (set_error(E_INCORRECT_ELEMENT));
			}
			j++;
		}
		i++;
	}
	return (OK);
}
