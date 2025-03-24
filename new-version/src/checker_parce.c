/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:52:29 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/24 09:26:15 by alouriga         ###   ########.fr       */
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

int	parce_color_help(int i, int j, char ***colors, char *line)
{
	while (line[j])
	{
		if (line[j] == ',')
			i++;
		j++;
	}
	*colors = ft_split(line, ',');
	if (i != 2)
		return (1);
	i = 0;
	while ((*colors)[i])
		i++;
	if (i != 3)
		return (1);
	return (0);
}

int	parse_color(char *line, int i, int j, int fd)
{
	int		r;
	int		g;
	int		b;
	char	**colors;

	colors = NULL;
	if (parce_color_help(i, j, &colors, line))
	{
		ft_error_2("Invalid RGB color format", fd);
	}
	if (check_spacee(colors) || check_again(colors))
	{
		ft_error_2("Invalid RGB color format", fd);
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_error_2("Invalid RGB color format", fd);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

int	parce_map_help(t_config *config, t_data *data,
					char **map_lines, t_parce *var)
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
