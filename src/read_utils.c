#include "types.h"
#include "error.h"
#include "read.h"
#include "libft.h"
#include <stdlib.h>

bool	ft_info_complete(t_parser *parse_info)
{
	if (!parse_info)
		return (false);
	if (parse_info->north == NULL)
		return (false);
	if (parse_info->south == NULL)
		return (false);
	if (parse_info->west == NULL)
		return (false);
	if (parse_info->east == NULL)
		return (false);
	if (parse_info->ceiling == NULL)
		return (false);
	if (parse_info->floor == NULL)
		return (false);
	return (true);
}

void	ft_free_parse_struct(t_parser *parse_info)
{
	if (parse_info)
	{
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

t_error	ft_init_parse_struct(t_parser	**parse_info)
{
	int	i;

	*parse_info = (t_parser *)malloc(sizeof(t_parser));
	if (!*parse_info)
		return (set_error(E_SYS));
	i = 0;
	while (i < 3)
	{
		(*parse_info)->f_colour[i] = -1;
		(*parse_info)->c_colour[i] = -1;
		i++;
	}
	(*parse_info)->face = '\0';
	(*parse_info)->north = NULL;
	(*parse_info)->south = NULL;
	(*parse_info)->east = NULL;
	(*parse_info)->west = NULL;
	(*parse_info)->ceiling = NULL;
	(*parse_info)->floor = NULL;
	return (OK);
}
