/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 16:14:59 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/20 15:49:25 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "error.h"
#include "parse/parser.h"
#include "init_game/game.h"
#include <fcntl.h>
#include <stdlib.h>

static t_error	ft_check_map_name(char *file)
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
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
		return (set_error(E_CALLOC));
	if (ft_parser(fd, file, *data) != OK)
	{
		close (fd);
		return (get_error());
	}
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
	printf("--px: %f, py: %f, face: %c\n", data->px, data->py, data->face);
	printf("--fov: %f\n", data->p_angle);
	printf("--height: %i, width: %i\n", data->height, data->width);
	int i = 0;
	while (i < data->height)
	{
		printf("%s##\n", data->map[i]);
		i++;
	}
}

static t_error	ft_cub3d(char *file)
{
	t_data	*data;
	int		fd;

	data = NULL;
	if (ft_check_map_name(file) != OK)
		return (get_error());
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (set_error(E_SYS));
	if (ft_init(fd, file, &data) != OK)
	{
		ft_free_data_struct(data);
		return (get_error());
	}
	// data->px = 11.5;
	// data->py = 9.75;
	ft_print_data_to_check(data);
	if (ft_init_game(&data) != OK)
	{
		ft_free_data_struct(data);
		return (get_error());
	}
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
