/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 14:12:40 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/01 15:23:48 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"
#include "libft.h"
#include <stdlib.h>

//TODO: this function only checks if the file ends with a '.cub'. 
//should we check other things?
t_error	ft_check_file_name(char *file, char *extension)
{
	int	i;

	if (!file)
		return (set_error(E_EMPTY_ARG));
	i = ft_strlen(file) - 4;
	if (i < 0)
		return (set_error(E_EXTENSION));
	if (ft_strcmp(&file[i], extension) != 0)
		return (set_error(E_EXTENSION));
	return (OK);
}

void	ft_free_data_struct(t_data *data)
{
	if (data)
	{
		if (data->map_grid)
			free(data->map_grid);
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