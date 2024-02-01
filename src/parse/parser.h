/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 13:44:28 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/02/01 18:13:20 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "error.h"
# include "types.h"

//parse_info
t_error	ft_parser(int fd, char *file, t_data *data);

//parse_map
t_error	ft_init_map(int fd, t_data **data, size_t start, char *file);

//validate_map
t_error	ft_validate_map(t_data *data);

//validate_path
t_error	ft_check_path(char *path, char **data_path);

//validate_colour
t_error	ft_check_colour(char *str, int *colours);

//parse_utils
t_error	ft_check_file_name(char *file, char *extension);
bool	ft_info_set(t_data *data);
bool	ft_is_empty_line(char *line);
void	ft_free_data_struct(t_data *data);

#endif
