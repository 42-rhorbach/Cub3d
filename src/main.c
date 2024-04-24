/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 16:14:59 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/03/29 15:18:09 by jvorstma      ########   odam.nl         */
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

static t_error	ft_init(int fd, char *file, t_data *data)
{
	if (ft_parser(fd, file, data) != OK)
	{
		close (fd);
		return (get_error());
	}
	return (OK);
}

static t_error	ft_cub3d(char *file)
{
	static t_data	data;
	int				fd;

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
