/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 14:13:21 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/07 11:35:07 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

bool	ft_info_set(t_data *data)
{
	if (data == NULL \
			|| data->north == NULL \
			|| data->south == NULL \
			|| data->west == NULL \
			|| data->east == NULL \
			|| data->c == 0 \
			|| data->f == 0)
		return (false);
	else
		return (true);
}

bool	ft_e_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (true);
	else
		return (false);
}

void	ft_free_data_struct(t_data *data)
{
	if (data)
	{
		if (data->map)
			ft_free_ptr_array((void **)data->map);
		if (data->north)
			free(data->north);
		if (data->south)
			free(data->south);
		if (data->west)
			free(data->west);
		if (data->east)
			free(data->east);
		free (data);
	}
}
