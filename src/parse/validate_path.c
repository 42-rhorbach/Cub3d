/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 18:06:22 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/03/29 14:44:27 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>

static t_error	ft_check_texture_name(char *file)
{
	int	i;

	if (!file)
		return (set_error(E_EMPTY_ARG));
	i = ft_strlen(file) - 4;
	if (i < 0)
		return (set_error(E_TEXTURE_EXTENSION));
	if (ft_strcmp(&file[i], ".png") != 0)
		return (set_error(E_TEXTURE_EXTENSION));
	return (OK);
}

t_error	ft_check_path(char *path, char **data_path)
{
//	int	fd;
//
//	fd = open(path, O_RDONLY);
//	if (fd == -1)
//		return (set_error(E_SYS));
//	close (fd);
// TODO: is this needed for opening/checking the texture files?
// you can delete if not needed, or adjust if needed in a different form.
	if (ft_check_texture_name(path) != OK)
		return (get_error());
	*data_path = ft_strdup(path);
	if (!*data_path)
		return (set_error(E_SYS));
	return (OK);
}
