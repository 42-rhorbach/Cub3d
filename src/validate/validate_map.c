/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:16:05 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/02/01 00:40:39 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"

t_error	ft_validate_map(t_parser *parse_info, t_data **data)
{
	(*data)->face = parse_info->face;
	(*data)->px = parse_info->px;
	(*data)->py = parse_info->py;
	return (OK);
}