/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 13:44:28 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/02/01 00:34:41 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "error.h"
# include "types.h"

t_error	ft_parser(int fd, char *file, t_parser **parse_info);
bool	ft_info_set(t_parser *parse_info);
void	ft_free_parse_struct(t_parser *parse_info);
bool	ft_is_empty_line(char *line);
t_error	ft_init_map(int fd, t_parser *parse_info, int start, char *file);
void	ft_free_data_struct(t_data *data); //needs to move to differnt file

#endif
