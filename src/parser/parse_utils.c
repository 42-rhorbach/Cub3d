/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvorstma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:13:21 by jvorstma          #+#    #+#             */
/*   Updated: 2024/01/25 14:13:26 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "error.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>

bool	ft_info_set(t_parser *parse_info)
{
	if (parse_info == NULL \
			|| parse_info->north == NULL \
			|| parse_info->south == NULL \
			|| parse_info->west == NULL \
			|| parse_info->east == NULL \
			|| parse_info->ceiling == NULL \
			|| parse_info->floor == NULL)
		return (false);
	else
		return (true);
}

void	ft_free_parse_struct(t_parser *parse_info)
{
	if (parse_info)
	{
		if (parse_info->map)
			ft_free_ptr_array((void **)parse_info->map);
		if (parse_info->north)
			free (parse_info->north);
		if (parse_info->south)
			free (parse_info->south);
		if (parse_info->east)
			free (parse_info->east);
		if (parse_info->west)
			free (parse_info->west);
		if (parse_info->ceiling)
			free (parse_info->ceiling);
		if (parse_info->floor)
			free(parse_info->floor);
		free (parse_info);
	}
}

bool	ft_is_empty_line(char *line)
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
