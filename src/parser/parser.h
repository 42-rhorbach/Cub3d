/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 13:44:28 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/01/25 13:44:30 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	char	face;
	char	*north;
	char	*east;
	char	*south;
	char	*west;
	char	*floor;
	char	*ceiling;
	char	**map;
}	t_parser;

t_error	ft_parser(int fd, char *file);
bool	ft_info_set(t_parser *parse_info);
void	ft_free_parse_struct(t_parser *parse_info);
bool	ft_is_empty_line(char *line);
t_error	ft_init_map(int fd, t_parser **parse_info, int start, char *file);

#endif
