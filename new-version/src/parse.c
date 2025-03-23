/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 05:08:35 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/23 16:55:01 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_spacee(char **colors)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (colors[i])
	{
		while (colors[i][j])
		{
			while (colors[i][j] && (colors[i][j] == ' '
				|| colors[i][j] == '\t'))
				j++;
			while (colors[i][j] && colors[i][j] != ' '
					&& colors[i][j] != '\t')
				j++;
			while (colors[i][j] && (colors[i][j] == ' '
					|| colors[i][j] == '\t'))
				j++;
			if (colors[i][j] && (colors[i][j] >= '0' && colors[i][j] <= '9'))
				return (1);
		}
		i++;
		j = 0;
	}
	return (0);
}

int	check_again(char **colors)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (colors[i])
	{
		while (colors[i][j])
		{
			if ((colors[i][j] >= '0' && colors[i][j] <= '9')
				|| colors[i][j] == ' ' || colors[i][j] == '\t')
				j++;
			else
				return (1);
		}
		i++;
		j = 0;
	}
	return (0);
}

void	parce_color_help(int i, int j, char ***colors, char *line)
{
	while (line[j])
	{
		if (line[j] == ',')
			i++;
		j++;
	}
	*colors = ft_split(line, ',');

	if (i != 2)
	{
		ft_error("Invalid RGB color format");
	}
	i = 0;
	while ((*colors)[i])
		i++;
	if (i != 3)
	{
		ft_error("Invalid RGB color format");
	}
}

static int	parse_color(char *line, int i, int j)
{
	int		r;
	int		g;
	int		b;
	char	**colors;
	
	colors = NULL;
	parce_color_help(i, j, &colors, line);
	if (check_spacee(colors) || check_again(colors))
	{
		ft_error("Invalid RGB color format");
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_error("Invalid RGB color format");
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static void	measure_map(char **lines, int *map_height,
							int *map_width, int line_count)
{
	int	i;
	int	width;

	*map_height = 0;
	*map_width = 0;
	i = 0;
	while (i < line_count)
	{
		width = ft_strlen(lines[i]);
		if (width > *map_width)
			*map_width = width;
		if (width > 0)
			(*map_height)++;
		i++;
	}
}

int	unit_player(t_data *data, char s, int col, int row)
{
	if ( s == 'N' || s == 'S' || s == 'E' || s == 'W')
	{
				data->player.x = col * TILE_UNIT + (TILE_UNIT / 2);
				data->player.y = row * TILE_UNIT + (TILE_UNIT / 2);
				if (s == 'N')
				data->player.angle = 3 * M_PI / 2;
				else if (s == 'S')
				data->player.angle = M_PI / 2;
				else if (s == 'E')
					data->player.angle = 0;
				else if (s == 'W')
					data->player.angle = M_PI;
				return (1);
	}
	return(0);
}


int parce_map_help(t_config *config, t_data *data, char **map_lines, t_parce *var)
{
	if (ft_strlen(map_lines[var->i]) == 0)
			return (1);
		config->map[var->row] = smart_malloc(config->map_width + 1);
		ft_memset(config->map[var->row], ' ', config->map_width);
		var->col = 0;
		var->line = map_lines[var->i];
		while (var->line[var->j] && var->col < config->map_width)
		{
			config->map[var->row][var->col] = var->line[var->j];
			if (unit_player(data, var->line[var->j], var->col, var->row))
				config->map[var->row][var->col] = '0';
			var->col++;
			var->j++;
		}
	return (0);
}

static void	parse_map(t_config *config, t_data *data,
	char **map_lines, int line_count)
{
	t_parce *var;

	var = smart_malloc(sizeof(t_parce));
	measure_map(map_lines, &config->map_height, &config->map_width, line_count);
	config->map = smart_malloc(sizeof(char *) * config->map_height);
	var->row = 0;
	var->i = 0;
	while (var->i < line_count && var->row < config->map_height)
	{
		var->j = 0;
		if (parce_map_help(config, data, map_lines, var))
			continue;
	config->map[var->row][config->map_width] = '\0';
	var->row++;
	var->i++;
}
}

int	len_cal(t_list *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		if (ft_strlen(list->str) > i)
			i = ft_strlen(list->str);
		list = list->next;
	}
	return (i);
}

char	**list_to_array(t_list *list)
{
	t_list	*lst;
	char	**map;
	int		i;
	int		len;

	i = 0;
	len = len_cal(list);
	lst = list;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	map = smart_malloc((i + 1) * sizeof(char *));
	i = 0;
	while (list)
	{
		map[i] = ft_strdup1(list->str, len);
		i++;
		list = list->next;
	}
	map[i] = NULL;
	i = 0;
	return (map);
}

int	check_sides(char **map1, int i, int j)
{
	while (map1[0][j])
	{
		while (map1[0][j] == ' ' || map1[0][j] == '\t')
			j++;
		if (map1[0][j] != '1' && map1[0][j] != ' '
				&& map1[0][j] != '\t' && map1[0][j] != '\n')
			return (1);
		j++;
	}
	j = 0;
	while (map1[i + 1])
		i++;
	while (map1[i][j])
	{
		while (map1[i][j] == ' ' || map1[i][j] == '\t')
			j++;
		if (map1[i][j] != '1' && map1[i][j] != ' '
				&& map1[i][j] != '\t' && map1[i][j] != '\n')
			return (1);
		j++;
	}
	return (0);
}

int	check_zero(char **map, int i, int j)
{
	if (map[i][j + 1] != '0' && map[i][j + 1] != '1'
			&& map[i][j + 1] != 'S' && map[i][j + 1] != 'W'
				&& map[i][j + 1] != 'E' && map[i][j + 1] != 'N')
		return (1);
	if (map[i][j - 1] != '0' && map[i][j - 1] != '1'
			&& map[i][j - 1] != 'S' && map[i][j - 1] != 'W'
				&& map[i][j - 1] != 'E' && map[i][j - 1] != 'N')
		return (1);
	if (map[i + 1][j] != '0' && map[i + 1][j] != '1'
			&& map[i + 1][j] != 'S' && map[i + 1][j] != 'W'
				&& map[i + 1][j] != 'E' && map[i + 1][j] != 'N')
		return (1);
	if (map[i - 1][j] != '0' && map[i - 1][j] != '1'
			&& map[i - 1][j] != 'S' && map[i - 1][j] != 'W'
				&& map[i - 1][j] != 'E' && map[i - 1][j] != 'N')
		return (1);
	return (0);
}

int parse_1_helper(char **map1, t_config **config, int i, int *j)
{
	if (map1[i][*j] == ' ' || map1[i][*j] == '\t')
	{
		(*j)++;
		return (2) ;
	}
	if (map1[i][*j] == 'S' || map1[i][*j] == 'N'
			|| map1[i][*j] == 'E' || map1[i][*j] == 'W')
	{
		if ((*config)->flag_player == 0)
			(*config)->flag_player = 1;
		else
			return (1);
	}
	if (map1[i][*j] == '0' || map1[i][*j] == 'N'
		|| map1[i][*j] == 'W' || map1[i][*j] == 'E'
			|| map1[i][*j] == 'S')
	{
		if (check_zero(map1, i, *j))
			return (1);
	}
	return (0);
}

int	parse_1(char **map1, t_config **config, int i, int j)
{
	int	x;

	while (map1[i])
	{
		if (check_sides(map1, 0, 0))
			return (1);
		if (!map1[i + 1])
			break ;
		while (map1[i][j])
		{
			x = parse_1_helper(map1, config, i, &j);
			if (x == 2)
				continue;
			if (x == 1)
				return(1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	check_line(char *line)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	if (line[0] == '\n')
		return (1);
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			index++;
		i++;
	}
	if (i == index)
		return (1);
	return (0);
}

void	unit_variables(t_config **config, t_vari **var, t_data *data)
{
	(*config) = &data->config;
	(*config)->width = WIDTH;
	(*config)->height = HEIGHT;
	(*config)->no_texture = NULL;
	(*config)->so_texture = NULL;
	(*config)->we_texture = NULL;
	(*config)->ea_texture = NULL;
	(*config)->flag_player = 0;
	(*config)->floor_color = 0;
	(*config)->ceil_color = 0;
	(*config)->map = NULL;
	(*var)->map_line_start = 0;
	(*var)->line_count = 0;
	(*var)->map_line_start = 0;
	(*var)->map_started = 0;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
int parce_name_file(const char *str, int index)
{
    int i = 0;
    while(*str && i < index - 4)
    {
        i++;
        str++;
    }
    if (ft_strcmp(str, ".cub"))
        return (1);
    return (0);
    
}
void	first_parce(t_vari **var, const char *filename)
{
	(*var) = smart_malloc(sizeof(t_vari));
	if (parce_name_file(filename, ft_strlen(filename)))
		ft_error("file name incorrect");
	(*var)->fd = open(filename, O_RDONLY);
	if ((*var)->fd < 0)
		ft_error("Cannot open .cub file");
}



void	parse_cub_file(const char *filename, t_data *data,
						int error_flag, t_list *list)
{
	t_list		*list_copy;
	t_config	*config;
	t_vari		*var;
	char		*trimmed;

	list_copy = NULL;
	first_parce(&var, filename);
	unit_variables(&config, &var, data);
	var->line = get_next_line(var->fd);
	while (var->line)
	{
		trimmed = ft_strtrim(var->line, " \t\n");
		if (*trimmed == '\0' && !var->map_started)
		{
			var->line = get_next_line(var->fd);
			continue ;
		}
		if (!var->map_started && ft_strncmp(trimmed, "NO ", 3) == 0
			&& !config->no_texture)
		{
			var->path_start = ft_strtrim(trimmed + 3, " \t\n");
			config->no_texture = ft_strdup(var->path_start);
		}
		else if (!var->map_started && ft_strncmp(trimmed, "SO ", 3) == 0
			&& !config->so_texture)
		{
			var->path_start = ft_strtrim(trimmed + 3, " \t\n");
			config->so_texture = ft_strdup(var->path_start);
		}
		else if (!var->map_started && ft_strncmp(trimmed, "WE ", 3) == 0
			&& !config->we_texture)
		{
			var->path_start = ft_strtrim(trimmed + 3, " \t\n");
			config->we_texture = ft_strdup(var->path_start);
		}
		else if (!var->map_started && ft_strncmp(trimmed, "EA ", 3) == 0
			&& !config->ea_texture)
		{
			var->path_start = ft_strtrim(trimmed + 3, " \t\n");
			config->ea_texture = ft_strdup(var->path_start);
		}
		else if (!var->map_started && ft_strncmp(trimmed, "F ", 2) == 0
			&& !config->floor_color)
		{
			var->color_str = ft_strtrim(trimmed + 2, " \t\n");
			config->floor_color = parse_color(var->color_str, 0, 0);
		}
		else if (!var->map_started && ft_strncmp(trimmed, "C ", 2) == 0
			&& !config->ceil_color)
		{
			var->color_str = ft_strtrim(trimmed + 2, " \t\n");
			config->ceil_color = parse_color(var->color_str, 0, 0);
		}
		else if (!var->map_started && ft_strchr("01NSEW ", *trimmed))
		{
			var->map_started = 1;
			error_flag = 1;
			var->map_line_start = var->line_count;
		}
		else if (!error_flag)
		{
			ft_error_2("parce error\n", var->fd);
		}
		if (var->map_started)
		{
			if (!config->no_texture || !config->so_texture
				|| !config->we_texture
				|| !config->ea_texture || !config->ceil_color
				|| !config->floor_color)
				ft_error_2("Missing required elements in .cub file", var->fd);
			if (check_line(var->line))
				ft_error_2("parsing map", var->fd);
			list_copy = ft_lstnew(var->line);
			ft_lstadd_back(&list, list_copy);
		}
		var->line_count++;
		var->line = get_next_line(var->fd);
	}
	close(var->fd);
	if (list)
		var->map1 = list_to_array(list);
	if ((var->map1 && parse_1(var->map1, &config, 0, 0)))
		ft_error("parsing map");
	if (!config->flag_player)
		ft_error("parsing map");
	if (var->map_started)
		parse_map(config, data, var->map1,
			var->line_count - var->map_line_start);
	if (!config->no_texture || !config->so_texture || !config->we_texture
		||!config->ea_texture)
		ft_error("Missing required elements in .cub file");
}
