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

//instead of mallocing 2 structs, and mallocing every value twice,
//do check overhere, return (validate_funct(struct->place, value))
//only the map needs validation after saving.

static t_error	ft_set_input(char *id, char *value, t_parser **parse_info)
{
	if (!value)
		return (set_error(E_EMPTY_ARG));
	if (ft_strcmp(id, "NO") == 0 && (*parse_info)->north == NULL)
		(*parse_info)->north = value;
	else if (ft_strcmp(id, "SO") == 0 && (*parse_info)->south == NULL)
		(*parse_info)->south = value;
	else if (ft_strcmp(id, "WE") == 0 && (*parse_info)->west == NULL)
		(*parse_info)->west = value;
	else if (ft_strcmp(id, "EA") == 0 && (*parse_info)->east == NULL)
		(*parse_info)->east = value;
	else if (ft_strcmp(id, "C") == 0 && (*parse_info)->ceiling == NULL)
		(*parse_info)->ceiling = value;
	else if (ft_strcmp(id, "F") == 0 && (*parse_info)->floor == NULL)
		(*parse_info)->floor = value;
	else
	{
		free(value);
		return (set_error(E_INV_INSTRC));
	}
	return (OK);
}

static t_error	ft_check_line(char	*trim_line, t_parser *parse_info)
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
	if (ft_set_input(buf[0], ft_strdup(buf[1]), &parse_info) != OK)
	{
		ft_free_ptr_array((void **)buf);
		return (get_error());
	}
	ft_free_ptr_array((void **)buf);
	return (OK);
}

t_error	ft_parser(int fd, char *file, t_parser **parse_info)
{
	char		*line;
	int			start;

	*parse_info = (t_parser *)ft_calloc(1, sizeof(t_parser));
	if (!*parse_info)
		return (set_error(E_CALLOC));
	start = 0;
	while (ft_info_set(*parse_info) == false \
			&& get_next_line(fd, &line) == GNL_CONTINUE)
	{
		start++;
		if (line && ft_is_empty_line(line) == false \
			&& ft_check_line(ft_strtrim(line, " \n"), *parse_info) != OK)
		{
			free(line);
			return (get_error());
		}
		free(line);
	}
	if (ft_init_map(fd, *parse_info, start, file) != OK)
		return (get_error());
	return (OK);
}
