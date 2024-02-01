/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 14:28:02 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/01 18:00:45 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

static t_error	ft_check_map_line(char *line, t_data **data, int i)
{
	int	j;

	j = 0;
	while (line && line[j] && line[j] != '\n')
	{
		if (line[j] == '0' || line[j] == '1' || line[j] == ' ')
			j++;
		else if (ft_strchr("NSWE", line[j]) != NULL && (*data)->face == '\0')
		{
			(*data)->face = line[j];
			(*data)->px = j;
			(*data)->py = i;
			j++;
		}
		else
			return (set_error(E_INCORRECT_ELEMENT));
	}
	(*data)->map_grid[i] = ft_strtrim(line, "\n");
	if (!line)
		return (set_error(E_SYS));
	free(line);
	return (OK);
}

static t_error	ft_fill_map(int fd, t_data *data, size_t start)
{
	size_t	i;
	char	*line;

	data->map_grid = (char **)ft_calloc((data->height + 1), sizeof(char *));
	if (!data->map_grid)
		return (set_error(E_CALLOC));
	i = 0;
	while (i++ < start && get_next_line(fd, &line) == GNL_CONTINUE)
		free(line);
	i = 0;
	while (i < data->height && get_next_line(fd, &line) == GNL_CONTINUE)
	{
		if (ft_check_map_line(line, &data, i) != OK)
		{
			free(line);
			return (get_error());
		}
		i++;
	}
	if (i != data->height || data->face == '\0')
		return (set_error(E_INV_INSTRC));
	return (OK);
}

static t_error	ft_get_map_size(int fd, size_t *start, size_t *size)
{
	char	*line;

	while (get_next_line(fd, &line) == GNL_CONTINUE \
			&& ft_is_empty_line(line) == true)
	{
		(*start)++;
		free(line);
	}
	while (line && ft_is_empty_line(line) == false)
	{
		(*size)++;
		free(line);
		if (get_next_line(fd, &line) == GNL_EOF)
			return (OK);
	}
	while (line && ft_is_empty_line(line) == true)
	{
		free(line);
		if (get_next_line(fd, &line) == GNL_EOF)
			return (OK);
	}
	if (line)
		free (line);
	return (set_error(E_INV_INSTRC));
}

t_error	ft_init_map(int fd, t_data **data, size_t start, char *file)
{
	int		new_fd;

	if (ft_get_map_size(fd, &start, &(*data)->height) != OK)
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
