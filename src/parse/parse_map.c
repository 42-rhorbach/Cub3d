/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 14:28:02 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/07 16:40:58 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>
#include <stdlib.h>

static t_error	ft_fill_line(char *line, t_data *data, int index)
{
	int	i;

	data->map[index] = (char *)malloc((data->width + 1) * sizeof(char));
	if (!data->map[index])
		return (set_error(E_SYS));
	i = 0;
	while (line[i] && line[i] != '\n' && i < data->width)
	{
		if (line[i] == data->face)
			data->map[index][i] = '0';
		else
			data->map[index][i] = line[i];
		i++;
	}
	while (i < data->width)
	{
		data->map[index][i] = ' ';
		i++;
	}
	data->map[index][i] = '\0';
	return (OK);
}

static t_error	ft_check_map_line(char *line, t_data **data, int i)
{
	int		j;

	j = 0;
	while (line[j] && line[j] != '\n')
	{
		if (line[j] == '0' || line[j] == '1' || line[j] == ' ')
			j++;
		else if (ft_strchr("ENWS", line[j]) != NULL && (*data)->face == '\0')
		{
			(*data)->face = line[j];
			(*data)->p_angle = 360;
			if (line[j] == 'N')
				(*data)->p_angle = 90;
			if (line[j] == 'W')
				(*data)->p_angle = 180;
			if (line[j] == 'S')
				(*data)->p_angle = 270;
			(*data)->px = j + 0.5;
			(*data)->py = i + 0.5;
			j++;
		}
		else
			return (set_error(E_INCORRECT_ELEMENT));
	}
	return (ft_fill_line(line, *data, i));
}

static t_error	ft_fill_map(int fd, t_data *data, int start)
{
	int		i;
	char	*line;

	data->map = (char **)ft_calloc((data->height + 1), sizeof(char *));
	if (!data->map)
		return (set_error(E_CALLOC));
	i = 0;
	while (i++ < start && get_next_line(fd, &line) == GNL_CONTINUE)
		free(line);
	i = 0;
	while (i < data->height && get_next_line(fd, &line) == GNL_CONTINUE)
	{
		if (!line)
			return (set_error(E_SYS));
		if (ft_check_map_line(line, &data, i) != OK)
		{
			free(line);
			return (get_error());
		}
		free(line);
		i++;
	}
	if (i != data->height || data->face == '\0')
		return (set_error(E_INV_INSTRC));
	return (OK);
}

static t_error	ft_get_map_size(int fd, int *start, t_data *data)
{
	char	*line;

	while (get_next_line(fd, &line) == GNL_CONTINUE && ft_e_line(line) == true)
	{
		(*start)++;
		free(line);
	}
	while (line && ft_e_line(line) == false)
	{
		data->height++;
		if (data->width < (int)ft_strlen(line) - 1)
			data->width = (int)ft_strlen(line) - 1;
		free(line);
		if (get_next_line(fd, &line) == GNL_EOF)
			return (OK);
	}
	while (line && ft_e_line(line) == true)
	{
		free(line);
		if (get_next_line(fd, &line) == GNL_EOF)
			return (OK);
	}
	if (line)
		free (line);
	return (set_error(E_INV_INSTRC));
}

t_error	ft_init_map(int fd, t_data **data, int start, char *file)
{
	int		new_fd;

	if (ft_get_map_size(fd, &start, *data) != OK)
		return (get_error());
	close (fd);
	new_fd = open(file, O_RDONLY);
	if (new_fd == -1)
		return (set_error(E_SYS));
	if (ft_fill_map(new_fd, *data, start) != OK)
	{
		close (new_fd);
		return (get_error());
	}
	close (new_fd);
	return (ft_validate_map(*data));
}
