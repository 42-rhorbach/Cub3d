
typedef struct s_parser
{
	char	face;
	char	*north;
	char	*east;
	char	*south;
	char	*west;
	char	*floor;
	char	*ceiling;
	int		f_colour[3];
	int		c_colour[3];
}	t_parser;

t_error	ft_read_and_parse(int fd);
bool	ft_info_complete(t_parser *parse_info);
void	ft_free_parse_struct(t_parser *parse_info);
t_error	ft_init_parse_struct(t_parser **parse_info);
