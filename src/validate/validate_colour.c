/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_colour.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:16:02 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/01/26 00:14:14 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"
#include "libft.h"

t_error	ft_check_colour(char *str, int *colours)
{
	int		i;
	int		c;
	char	**s_str;

	s_str = ft_split(str, ',');
	if (ft_ptr_array_length((void **)s_str) != 3)
	{
		ft_free_ptr_array((void **)s_str);
		return (set_error(E_INCORRECT_ELEMENT));
	}
	i = 0;
	while (s_str[i])
	{
		c = ft_atoi(s_str[i]);
		if (c < 0 || c > 255)
		{
			ft_free_ptr_array((void **)s_str);
			return (set_error(E_INCORRECT_ELEMENT));
		}
		colours[i] = c;
		i++;
	}
	ft_free_ptr_array((void **)s_str);
	return (OK);
}
