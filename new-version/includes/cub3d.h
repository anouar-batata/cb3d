#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"

#define WIDTH 1200
#define HEIGHT 1000
#define FOV 60
#define TILE_UNIT 64

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_list
{
	char		*str;
	struct s_list	*next;
}	t_list;

typedef struct s_config
{
	int		width;
	int		height;
	char		*no_texture;
	int		flag_player;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	uint32_t	floor_color;
	uint32_t	ceil_color;
	char		**map;
	int		map_width;
	int		map_height;
}	t_config;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_config	config;
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
}	t_data;

typedef struct s_vari
{
	char **map1;
	char *line;
	char *path_start;
	int map_started;
	int line_count;
	int map_line_start;
	char *color_str;
	int			fd;
} t_vari;



typedef struct s_node
{
	void			*ptr;
	struct s_node	*next;
}	t_node;


typedef struct s_parce
{
	int		row;
	int		i;
	int		j;
	int		col;
	char	*line;
} t_parce;

typedef struct s_ray_step
{
	int	step_x;
	int	step_y;
	double	side_dist_x;
	double	side_dist_y;
}	t_ray_step;

typedef struct s_ray
{
	double	angle;
	double	dx;
	double	dy;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_x;
	int	side;
	double	dist;
	int	hit;
}	t_ray;


t_node	*ft_lstnew8(void *ptr_to_store);
void	first_parce(t_vari **var, const char *filename);
int	parce_helper_2(char *trimmed, t_vari **var, t_config **config);
int	parce_helper_1(char *trimmed, t_vari **var, t_config **config);
void	parce_first_arguments_2(t_vari *var, t_config *config, t_list *list_copy, t_list **list);
int parse_1_helper(char **map1, t_config **config, int i, int *j);
int	parse_1(char **map1, t_config **config, int i, int j);
void	unit_variables(t_config **config, t_vari **var, t_data *data);
int parce_name_file(const char *str, int index);
int	check_line(char *line);
int	check_sides(char **map1, int i, int j);
int	check_zero(char **map, int i, int j);
void	measure_map(char **lines, int *map_height,
    int *map_width, int line_count);
void	parse_map(t_config *config, t_data *data,
		char **map_lines, int line_count);
int	unit_player(t_data *data, char s, int col, int row);
int	check_spacee(char **colors);
int	check_again(char **colors);
int	parse_color(char *line, int i, int j, int fd);
int	parce_color_help(int i, int j, char ***colors, char *line);
int	parce_map_help(t_config *config, t_data *data, char **map_lines, t_parce *var);
int	len_cal(t_list *list);
char	**list_to_array(t_list *list);	
int	ft_strcmp(const char *s1, const char *s2);
void ft_error_2(const char *str, int fd);
void	*smart_malloc(size_t size);
void	smart_free(void);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	parse_cub_file(const char *filename, t_data *data, t_list *list);
void    ft_error(const char *str);
void    load_textures(t_data *data);
void    free_textures(t_data *data);
void	ft_render(void *param);
void	ft_hook(void *param);
double	cast_ray(t_data *data, t_ray *ray);
double	to_radian(int value);
void	draw_ceil_and_floor(t_data *data);
void	move_forward(t_data *data, double move_speed);
void	move_backward(t_data *data, double move_speed);
void	turn_right(t_data *data, double rot_speed);
void	turn_left(t_data *data, double rot_speed);
char	*ft_strdup1(const char *s1, int len);
void	move_right(t_data *data, double move_speed);
void	move_left(t_data *data, double move_speed);

#endif