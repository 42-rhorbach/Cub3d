/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvorstma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:28:02 by jvorstma          #+#    #+#             */
/*   Updated: 2024/01/25 14:28:03 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "error.h"
#include "parser.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

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
	while (i < size && get_next_line(fd, &(*info)->map[i]) == GNL_CONTINUE)
		i++;
	if (i != size)
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
//return ok in while loops if EOF is reached while not have empty lines, 
//or after map if only having empty lines.
// if it gets out of those loops before eof, 
//something went wrong in gnl or there are illegal instructions in the file.

t_error	ft_init_map(int fd, t_parser **parse_info, int start, char *file)
{
	int		size;
	int		new_fd;

	size = 0;
	if (ft_get_map_size(fd, &start, &size) != OK)
		return (get_error());
	close (fd);
	new_fd = open(file, O_RDONLY);
	if (new_fd == -1)
		return (set_error(E_SYS));
	if (ft_fill_map(new_fd, &(*parse_info), start, size) != OK)
	{
		close (new_fd);
		return (get_error());
	}
	close (new_fd);
	return (OK);
}
