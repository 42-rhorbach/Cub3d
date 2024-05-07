/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 18:06:22 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/05/07 16:46:40 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

t_error	ft_check_path(char *path, char **data_path)
{
	int	fd;
	int	i;

	if (!path)
		return (set_error(E_EMPTY_ARG));
	i = ft_strlen(path) - 4;
	if (i < 0 || ft_strcmp(&path[i], ".png") != 0)
		return (set_error(E_TEXTURE_EXTENSION));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (set_error(E_SYS));
	close (fd);
	*data_path = ft_strdup(path);
	if (!*data_path)
		return (set_error(E_SYS));
	return (OK);
}
