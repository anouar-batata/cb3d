/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parce_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:59:15 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/24 09:30:09 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	measure_map(char **lines, int *map_height,
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
	if (s == 'N' || s == 'S' || s == 'E' || s == 'W')
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
	return (0);
}

void	parse_map(t_config *config, t_data *data,
	char **map_lines, int line_count)
{
	t_parce	*var;

	var = smart_malloc(sizeof(t_parce));
	measure_map(map_lines, &config->map_height, &config->map_width, line_count);
	config->map = smart_malloc(sizeof(char *) * config->map_height);
	var->row = 0;
	var->i = 0;
	while (var->i < line_count && var->row < config->map_height)
	{
		var->j = 0;
		if (parce_map_help(config, data, map_lines, var))
			continue ;
		config->map[var->row][config->map_width] = '\0';
		var->row++;
		var->i++;
	}
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
