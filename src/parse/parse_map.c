/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 14:28:02 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/01 00:37:12 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

static t_error	ft_check_map_line(char *line, t_parser *info, int i)
{
	int	j;

	j = 0;
	while (line && line[j] && line[j] != '\n')
	{
		if (line[j] == '0' || line[j] == '1' || line[j] == ' ')
			j++;
		else if (ft_strchr("NSWE", line[j]) != NULL && info->face == '\0')
		{
			info->face = line[j];
			info->px = j;
			info->py = i;
			j++;
		}
		else
			return (set_error(E_INCORRECT_ELEMENT));
	}
	info->map[i] = ft_strtrim(line, "\n");
	if (!line)
		return (set_error(E_SYS));
	free(line);
	return (OK);
}

static t_error	ft_fill_map(int fd, t_parser **info, int start, int size)
{
	int		i;
	char	*line;

	(*info)->map = (char **)ft_calloc((size + 1), sizeof(char *));
	if (!(*info)->map)
		return (set_error(E_CALLOC));
	i = 0;
	while (i++ < start && get_next_line(fd, &line) == GNL_CONTINUE)
		free(line);
	i = 0;
	while (i < size && get_next_line(fd, &line) == GNL_CONTINUE)
	{
		if (ft_check_map_line(line, *info, i) != OK)
		{
			free(line);
			return (get_error());
		}
		i++;
	}
	(*info)->map[i] = NULL;
	if (i != size || (*info)->face == '\0')
		return (set_error(E_INV_INSTRC));
	return (OK);
}

static t_error	ft_get_map_size(int fd, int *start, int *size)
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

t_error	ft_init_map(int fd, t_parser *parse_info, int start, char *file)
{
	int		size;
	int		new_fd;

	size = 0;
	if (ft_get_map_size(fd, &start, &size) != OK)
	{
		ft_free_parse_struct(parse_info);
		return (get_error());
	}
	close (fd);
	new_fd = open(file, O_RDONLY);
	if (new_fd == -1)
	{
		ft_free_parse_struct(parse_info);
		return (set_error(E_SYS));
	}
	if (ft_fill_map(new_fd, &parse_info, start, size) != OK)
	{
		close (new_fd);
		ft_free_parse_struct(parse_info);
		return (get_error());
	}
	close (new_fd);
	return (OK);
}
