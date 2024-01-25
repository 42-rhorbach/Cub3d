/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:14:48 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/01/26 00:22:04 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"
#include "libft.h"

static t_error ft_check_path(char *path, char **data_path)
{
	*data_path = ft_strdup(path);
	if (!*data_path)
		return (set_error(E_SYS));
	return (OK);
}

t_error ft_validate_data(t_parser *parse_info, t_data *data)
{
	if (ft_check_colour(parse_info->ceiling, data->ceiling) != OK \
		|| ft_check_colour(parse_info->floor, data->floor) != OK \
		|| 	ft_check_path(parse_info->north, &data->north) != OK \
		|| 	ft_check_path(parse_info->south, &data->south) != OK \
		|| 	ft_check_path(parse_info->west, &data->west) != OK \
		|| 	ft_check_path(parse_info->east, &data->east) != OK)
	{
		ft_free_parse_struct(parse_info);
		return (set_error(E_INCORRECT_ELEMENT));
	}
	ft_free_parse_struct(parse_info);
	return (OK);
}