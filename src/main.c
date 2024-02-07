/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 16:14:59 by rhorbach      #+#    #+#                 */
/*   Updated: 2024/02/07 23:43:04 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "libft.h"
#include "error.h"
#include "parse/parser.h"
#include <fcntl.h>
#include "error.h"
#include <stdlib.h>

static t_error	ft_check_map_name(char *file)
{
	int	i;

	if (!file)
		return (set_error(E_EMPTY_ARG));
	i = ft_strlen(file) - 4;
	if (i < 0)
		return (set_error(E_EXTENSION));
	if (ft_strcmp(&file[i], ".cub") != 0)
		return (set_error(E_EXTENSION));
	return (OK);
}

static t_error	ft_init(int fd, char *file, t_data **data)
{
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
		return (set_error(E_CALLOC));
	if (ft_parser(fd, file, *data) != OK)
	{
		close (fd);
		return (get_error());
	}
	return (OK);
}

static void	ft_print_data_to_check(t_data *data)
{
	printf("printing for checking:\n");
	printf("--north: %s\n", data->north);
	printf("--south: %s\n", data->south);
	printf("--east: %s\n", data->east);
	printf("--west: %s\n", data->west);
	printf("--ceiling: %i,%i,%i\n", data->ceiling[0], data->ceiling[1], data->ceiling[2]);
	printf("--floor: %i,%i,%i\n", data->floor[0], data->floor[1], data->floor[2]);
	printf("--px: %i, py: %i, face: %c\n", data->px, data->py, data->face);
	printf("--height: %i, width: %i\n", data->height, data->width);
	int i = 0;
	while (i < data->height)
	{
		printf("%s##\n", data->map[i]);
		i++;
	}
}

static t_error	ft_cub3d(char *file)
{
	t_data	*data;
	int		fd;

	data = NULL;
	if (ft_check_map_name(file) != OK)
		return (get_error());
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (set_error(E_SYS));
	if (ft_init(fd, file, &data) != OK)
	{
		ft_free_data_struct(data);
		return (get_error());
	}
	ft_print_data_to_check(data);
	ft_free_data_struct(data);
	return (OK);
}
#include <fcntl.h>

//------------------------------------------------------------------------------

// void	turn_player(t_data *data, ...) //TODO: Make

void	move_player(t_data *data, int dx, int dy)
{
	const int	tx = data->px + dx;
	const int	ty = data->py + dy;

	if (data->map_grid[ty][tx] == '1')
		return ;
	data->px = tx;
	data->py = ty;
	data->images[PLAYER]->instances[0].x = data->px;
	data->images[PLAYER]->instances[0].y = data->py;
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data *const	data = param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);
		if (keydata.key == MLX_KEY_W)
			move_player(data, 0, -1);
		if (keydata.key == MLX_KEY_S)
			move_player(data, 0, 1);
		if (keydata.key == MLX_KEY_A)
			move_player(data, -1, 0);
		if (keydata.key == MLX_KEY_D)
			move_player(data, 1, 0);
		if (keydata.key == MLX_KEY_LEFT)
			//turn_player(data, ...);?
		if (keydata.key == MLX_KEY_RIGHT)
			//turn_player(data, ...);?
	}
}

//------------------------------------------------------------------------------

static t_list	*get_map_lines(int map_fd)
{
	t_list	*head;
	char	*new_line;
	t_gnl	gnl;

	head = NULL;
	while (true)
	{
		gnl = get_next_line(map_fd, &new_line);
		if (gnl == GNL_ERROR)
		{
			ft_lstclear(&head, &free);
			return (NULL);
		}
		if (gnl == GNL_EOF)
			break ;
		if (new_line[ft_strlen(new_line) - 1] == '\n')
			new_line[ft_strlen(new_line) - 1] = '\0';
		if (ft_lstnew_front(&head, new_line) == NULL)
		{
			free(new_line);
			ft_lstclear(&head, &free);
			return (NULL);
		}
	}
	return (head);
}

static char	**load_map_grid(int map_fd)
{
	t_list	*lst;
	char	**map_grid;

	lst = get_map_lines(map_fd);
	if (lst == NULL)
		return (NULL);
	map_grid = (char **)ft_lst_to_array_rev(lst);
	if (map_grid == NULL)
	{
		ft_lstclear(&lst, &free);
		return (NULL);
	}
	ft_lstclear(&lst, NULL);
	return (map_grid);
}

char	**proto_load_map(const char *file)
{
	int		map_fd;
	char	**map_grid;

	map_fd = open(file, O_RDONLY);
	if (map_fd < 0)
		return (NULL);
	map_grid = load_map_grid(map_fd);
	close(map_fd);
	return (map_grid);
}

/*
void proto_load_config(void)
{

}
*/

t_error	proto_load_file(t_data *data, const char *file) //temp
{
	//TODO: make proto_load_config();

	data->map_grid = proto_load_map(file);
	if (data->map_grid == NULL)
		return (set_error(E_SYS));
	return (OK);
}

t_error	proto_parse_file(t_data *data, const char *file) //temp
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (set_error(E_EXTENSION));
	if (ft_strncmp(&file[len - 4], ".cub", 5) != 0)
		return (set_error(E_EXTENSION));
	if (proto_load_file(data, file) != OK)
		return (ERROR);
	//only for simple rectangles maps
	//TODO: all map shapes and sizes
	data->height = ft_ptr_array_length((void **)data->map_grid);
	data->width = 0;
	if (data->height != 0)
		data->width = ft_strlen(data->map_grid[0]);
	//TODO: [partner] validate maps
	return (OK);
}

//------------------------------------------------------------------------------

// t_error	instantiate_map(t_data *data) //TODO: reuse to make minimap of sorts?
// {
// 	size_t			x;
// 	size_t			y;
// 	t_texture_index	tile_type;

// 	y = 0;
// 	while (y < data->height)
// 	{
// 		x = 0;
// 		while (x < data->width)
// 		{
// 			if (create_instance(data, FLOOR, x, y) != OK)
// 				return (get_error());
// 			tile_type = get_tile_type(data->map_grid[y][x]);
// 			if (tile_type != FLOOR)
// 			{
// 				if (create_instance(data, tile_type, x, y) != OK)
// 					return (get_error());
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (OK);
// }

// static t_error	load_texture(t_data *data, const char *texture_path,
// 								mlx_image_t **img)
// {
// 	mlx_texture_t	*texture;

// 	texture = mlx_load_png(texture_path);
// 	if (texture == NULL)
// 		return (set_error(E_MLX));
// 	*img = mlx_texture_to_image(data->mlx, texture);
// 	mlx_delete_texture(texture);
// 	if (*img == NULL)
// 		return (set_error(E_MLX));
// 	return (OK);
// }

t_error	window_init(t_data *data) //TODO: instantiate map which can be viewed 1st person
{
	data->mlx = mlx_init(1024, 512, "cub3d", false); //standaard medium windowsize
	if (data->mlx == NULL)
		return (set_error(E_MLX));

	// if (load_texture(data, SL_TEX "exit.png", &data->images[EXIT]) != OK \
	// || load_texture(data, SL_TEX "floor.png", &data->images[FLOOR]) != OK \
	// || load_texture(data, SL_TEX "hatch.png", &data->images[HATCH]) != OK \
	// || load_texture(data, SL_TEX "player.png", &data->images[PLAYER]) != OK \
	// || load_texture(data, SL_TEX "shiny.png", &data->images[SHINY]) != OK \
	// || load_texture(data, SL_TEX "wall.png", &data->images[WALL]) != OK)
	// 	return (get_error());
	if (instantiate_map(data) != OK)
		return (get_error());
	return (OK);
}

//------------------------------------------------------------------------------

/**
 * Free everything in data (does not free data itself)
 * @param data address of bzero'd t_data struct
*/
void	free_data_content(t_data *data)
{
	if (data->map_grid != NULL)
		ft_free_ptr_array((void **)data->map_grid);
}

t_error	cub3d(char	*file)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (proto_parse_file(&data, file) != OK) //dit kan vervangen worden nu
		return (get_error());
	data.mlx = NULL;
	if (window_init(&data) != OK)
	{
		if (data.mlx != NULL)
		{
			mlx_close_window(data.mlx);
			mlx_terminate(data.mlx);
		}
		free_data_content(&data);
		return (get_error());
	}
	// data.px = data.images[PLAYER]->instances[0].x / TILE_SIZE;
	// data.py = data.images[PLAYER]->instances[0].y / TILE_SIZE;
	//TODO: define player position in parsing N,S,W,E
	mlx_key_hook(data.mlx, &ft_hook, &data);
	mlx_loop(data.mlx);
	free_data_content(&data);
	mlx_terminate(data.mlx);

}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error(E_ARGC);
		return (EXIT_FAILURE);
	}
	if (ft_cub3d(argv[1]) != OK)
	{
		print_error(get_error());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
