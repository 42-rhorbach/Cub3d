/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 16:14:59 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/01/18 16:14:59 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include "error.h"
#include "parse/parser.h"
#include "validate/validate.h"
#include <fcntl.h>
#include <stdlib.h>

//TODO: this function only checks if the file ends with a '.cub'. 
//should we check other things?
static t_error	ft_check_file_name(char *file)
{
	int	i;

	if (!file)
		return (set_error(E_EMPTY_ARG));
	i = ft_strlen(file) - 4;
	if (i < 0)
		return (set_error(E_EXTENSION));
	if (ft_strcmp(&file[i], ".cub") != 0)
		return (set_error(E_EXTENSION));
	return (OK);
}

static t_error	ft_init(int fd, char *file, t_data **data)
{
	t_parser	*parse_info;

	parse_info = NULL;
	if (ft_parser(fd, file, &parse_info) != OK)
	{
		close (fd);
		ft_free_parse_struct(parse_info);
		return (get_error());
	}
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
	{
		ft_free_parse_struct(parse_info);
		return (set_error(E_CALLOC));
	}
	if (ft_validate_data(parse_info, *data) != OK)
		return (get_error());
	return (OK);
}

static void	ft_print_data_to_check(t_data *data)
{
	printf("printing for checking:\n");
	printf("--north: %s\n", data->north);
	printf("--south: %s\n", data->south);
	printf("--east: %s\n", data->east);
	printf("--west: %s\n", data->west);
	printf("--ceiling: %i,%i,%i\n", data->ceiling[0], data->ceiling[1], data->ceiling[2]);
	printf("--floor: %i,%i,%i\n", data->floor[0], data->floor[1], data->floor[2]);
	printf("--px: %i, py: %i, face: %c\n", data->px, data->py, data->face);
}

static t_error	ft_cub3d(char *file)
{
	t_data	*data;
	int		fd;

	data = NULL;
	if (ft_check_file_name(file) != OK)
		return (get_error());
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (set_error(E_SYS));
	if (ft_init(fd, file, &data) != OK)
	{
		ft_free_data_struct(data);
		return (get_error());
	}
	ft_print_data_to_check(data);
	ft_free_data_struct(data);
	return (OK);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error(E_ARGC);
		return (EXIT_FAILURE);
	}
	if (ft_cub3d(argv[1]) != OK)
	{
		print_error(get_error());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
