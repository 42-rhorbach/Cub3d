/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 13:52:36 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/01/18 16:03:59 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include "MLX42.h"
#include <stdio.h>

static t_error	*get_error_ptr(void)
{
	static t_error	err_ptr = OK;

	return (&err_ptr);
}

t_error	set_error(t_error err)
{
	t_error	*err_ptr;

	err_ptr = get_error_ptr();
	*err_ptr = err;
	return (*err_ptr);
}

t_error	get_error(void)
{
	t_error	*err_ptr;

	err_ptr = get_error_ptr();
	return (*err_ptr);
}

//TODO: added some preset messages from so_long, check which are redundant.
void	print_error(t_error err)
{
	static const char	*error_table[] = {
	[E_ARGC] = "Program takes only one argument.",
	[E_EMPTY_ARG] = "Passed argument is empty.",
	[E_CALLOC] = "Calloc failed.",
	[E_NO_MAP] = "Received empty map.",
	[E_EXTENSION] = "Map file must end with \".cub\".",
	[E_TEXTURE_EXTENSION] = "Texture file must end with \".png\".",
	[E_MAP_NOT_CLOSED] = "Map is not enclosed by walls.",
	[E_INCORRECT_ELEMENT] = "Unknown symbol found in map.",
	[E_WRONG_QUANTITY] = "Too many/few players in map.",
	[E_INV_INSTRC] = "Invalid file content.",
	[E_INCORRECT_COLOUR] = "One of the colour codes in incorrect.",
	[E_ELEMENT_MISSING] = "A element is missing.",
	};

	ft_putendl_fd("Error", STDERR_FILENO);
	if (err == E_MLX)
	{
		ft_putstr_fd("cub3d: ", STDERR_FILENO);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	}
	else if (err == E_SYS)
		perror("cub3d");
	else
	{
		ft_putstr_fd("cub3d: ", STDERR_FILENO);
		ft_putendl_fd((char *)error_table[err], STDERR_FILENO);
	}
}
