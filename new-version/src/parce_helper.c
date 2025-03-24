/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:04:55 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/24 22:03:13 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_1_helper(char **map1, t_config **config, int i, int *j)
{
	if (map1[i][*j] == ' ' || map1[i][*j] == '\t')
	{
		(*j)++;
		return (2);
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
				continue ;
			if (x == 1)
				return (1);
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
	(*var)->map1 = NULL;
}

int	parce_name_file(const char *str, int index)
{
	int	i;

	i = 0;
	while (*str && i < index - 4)
	{
		i++;
		str++;
	}
	if (ft_strcmp(str, ".cub"))
		return (1);
	return (0);
}
