/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <jvorstma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 03:17:32 by jvorstma      #+#    #+#                 */
/*   Updated: 2024/01/26 00:04:21 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_H
# define VALIDATE_H

# include "types.h"
# include "../parse/parser.h"
# include "error.h"

t_error ft_validate_data(t_parser *parse_info, t_data *data);
t_error ft_check_colour(char *str, int *colours);

#endif