/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_info.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 09:10:54 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/01/25 09:10:54 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

static t_error	ft_set_input(char *id, char *value, t_data *data)
{
	if (!value)
		return (set_error(E_EMPTY_ARG));
	if (ft_strcmp(id, "NO") == 0 && data->north == NULL)
		return (ft_check_path(value, &data->north));
	else if (ft_strcmp(id, "SO") == 0 && data->south == NULL)
		return (ft_check_path(value, &data->south));
	else if (ft_strcmp(id, "WE") == 0 && data->west == NULL)
		return (ft_check_path(value, &data->west));
	else if (ft_strcmp(id, "EA") == 0 && data->east == NULL)
		return (ft_check_path(value, &data->east));
	else if (ft_strcmp(id, "C") == 0 && data->c == 0)
		return (ft_check_colour(value, data->ceiling, &data->c));
	else if (ft_strcmp(id, "F") == 0 && data->f == 0)
		return (ft_check_colour(value, data->floor, &data->f));
	else
		return (set_error(E_INV_INSTRC));
}

static t_error	ft_check_line(char	*trim_line, t_data **data)
{
	char	**buf;

	if (!trim_line)
		return (set_error(E_EMPTY_ARG));
	buf = ft_split(trim_line, ' ');
	if (!buf)
	{
		free(trim_line);
		return (set_error(E_SYS));
	}
	free(trim_line);
	if (ft_ptr_array_length((void **)buf) != 2)
	{
		ft_free_ptr_array((void **)buf);
		return (set_error(E_INV_INSTRC));
	}
	if (ft_set_input(buf[0], buf[1], *data) != OK)
	{
		ft_free_ptr_array((void **)buf);
		return (get_error());
	}
	ft_free_ptr_array((void **)buf);
	return (OK);
}

t_error	ft_parser(int fd, char *file, t_data *data)
{
	char	*line;
	size_t	start;

	start = 0;
	while (ft_info_set(data) == false \
			&& get_next_line(fd, &line) == GNL_CONTINUE)
	{
		start++;
		if (line && ft_e_line(line) == false \
			&& ft_check_line(ft_strtrim(line, " \n"), &data) != OK)
		{
			free(line);
			return (get_error());
		}
		free(line);
	}
	if (ft_info_set(data) == false)
		return (set_error(E_ELEMENT_MISSING));
	if (ft_init_map(fd, &data, start, file) != OK)
		return (get_error());
	return (OK);
}
