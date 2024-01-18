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
#include <fcntl.h>
#include <stdlib.h>

 //this function only checks if the file ends with a '.cub'. should we check other things?
static t_error	ft_check_file_name(char *file)
{
	int	i;

	if (!file)
		return (set_error(E_EMPTY_ARG));
	i = ft_strlen(file) - 4;
	if (i < 0 || !file[i])
		return (set_error(E_EXTENSION));
	if (ft_strcmp(&file[i], ".cub") != 0)
		return (set_error(E_EXTENSION));
	return (OK);
}

static t_error	cub3d(char	*file)
{
	int	fd;

	if (!file)
		return (set_error(E_EMPTY_ARG));
	if (ft_check_file_name(file) != OK)
		return (get_error());
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (set_error(E_SYS));
	if (ft_read_and_parse(fd) != OK)
		return (get_error());
	close (fd);
	return (OK);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error(E_ARGC);
		return (EXIT_FAILURE);
	}
	if (cub3d(argv[1]) != OK)
	{
		print_error(get_error());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
