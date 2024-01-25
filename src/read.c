/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvorstma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:48:25 by jvorstma          #+#    #+#             */
/*   Updated: 2024/01/18 18:48:28 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "error.h"
#include "read.h"
#include "libft.h"
#include <stdlib.h>

static t_error	ft_set_input(char *line1, char *line2, t_parser **parse_info)
{
	if (!line2)
		return (set_error(E_EMPTY_ARG));
	if (!line1 || !parse_info)
		return (free(line2), set_error(E_EMPTY_ARG));
	if (ft_strcmp(line1, "NO") == 0 && (*parse_info)->north == NULL)
		(*parse_info)->north = line2;
	else if (ft_strcmp(line1, "SO") == 0 && (*parse_info)->south == NULL)
		(*parse_info)->south = line2;
	else if (ft_strcmp(line1, "WE") == 0 && (*parse_info)->west == NULL)
		(*parse_info)->west = line2;
	else if (ft_strcmp(line1, "EA") == 0 && (*parse_info)->east == NULL)
		(*parse_info)->east = line2;
	else if (ft_strcmp(line1, "C") == 0 && (*parse_info)->ceiling == NULL)
		(*parse_info)->ceiling = line2;
	else if (ft_strcmp(line1, "F") == 0 && (*parse_info)->floor == NULL)
		(*parse_info)->floor = line2;
	else
		return (free(line2), set_error(E_INV_INSTRC));
	return (OK);
}

static t_error	ft_check_line(char	*trim_line, t_parser **parse_info)
{
	char	**buf;

	if (!trim_line)
		return (set_error(E_EMPTY_ARG));
	if (!parse_info)
		return (free(trim_line), set_error(E_EMPTY_ARG));
	if (trim_line[0] && trim_line[0] != '\0')
	{
		buf = ft_split(trim_line, ' ');
		if (trim_line)
			free(trim_line);
		if (buf && ft_ptr_array_length((void **)buf) == 2)
			if (ft_set_input(buf[0], ft_strdup(buf[1]), parse_info) != OK)
				return (ft_free_ptr_array((void **)buf), get_error());
		if (buf)
			ft_free_ptr_array((void **)buf);
	}
	else
		free(trim_line);
	return (OK);
}

static t_error	ft_new_map(char *line, t_parser **parse_info, int size)
{
	char	**buf;
	int		i;

	i = 0;
	if (!line)
		return (set_error(E_EMPTY_ARG));
	buf = (char **)malloc((size + 1) * sizeof(char *));
	if (!buf)
		return (free(line), set_error(E_SYS));
	while (i < (size - 1) && (*parse_info)->map)
	{
		ft_putstr_fd((*parse_info)->map[i], 1);
		buf[i] = ft_strdup((*parse_info)->map[i]);
		ft_putendl_fd(buf[i], 1);
		if (!buf[i])
		{
			while (--i >= 0 && buf[i])
				free(buf[i]);
			free(buf);
			free(line);
			return (set_error(E_SYS));
		}
		i++;
	}
	ft_putendl_fd(line, 1);
	buf[size - 1] = line;
	ft_putendl_fd(buf[size - 1], 1);
	buf[size] = NULL;
	ft_free_ptr_array((void **)(*parse_info)->map);
	(*parse_info)->map = buf;
	return (OK);
}

static t_error	ft_get_map(int fd, char *line, t_parser **parse_info)
{
	int		size;

	if (!line)
		return (set_error(E_EMPTY_ARG));
	if (!parse_info)
		return (free(line), set_error(E_EMPTY_ARG));
	size = 0;
	while (line)
	{
		size += 1;
		if (ft_new_map(line, &(*parse_info), size) != OK)
			return (get_error());
		if (get_next_line(fd, &line) != GNL_CONTINUE)
			break ;
	}
	return (OK);
}

t_error	ft_read_and_parse(int fd)
{
	t_parser	*parse_info;
	char		*line;

	parse_info = NULL;
	if (ft_init_parse_struct(&parse_info) != OK)
		return (get_error());
	while (!ft_info_set(parse_info) && get_next_line(fd, &line) == GNL_CONTINUE)
	{
		if (ft_check_line(ft_strtrim(line, " \n"), &parse_info) != OK)
		{
			if (line)
				free(line);
			return (ft_free_parse_struct(parse_info), get_error());
		}
		free(line);
	}
	while (get_next_line(fd, &line) == GNL_CONTINUE && !ft_strchr(line, '1'))
		free(line);
	if (ft_get_map(fd, line, &parse_info) != OK)
		return (ft_free_parse_struct(parse_info), get_error());
	return (ft_free_parse_struct(parse_info), OK);
}
