/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:31:34 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/24 23:31:36 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(const char *str)
{
	smart_free();
	printf("Error\n%s", str);
	exit(1);
}

static void	free_config_textures(t_data *data)
{
	if (data->config.ea_texture)
		free(data->config.ea_texture);
	if (data->config.we_texture)
		free(data->config.we_texture);
	if (data->config.no_texture)
		free(data->config.no_texture);
	if (data->config.so_texture)
		free(data->config.so_texture);
}

double	to_radian(int value)
{
	return (value * M_PI / 180.0);
}

void	free_config(t_data *data)
{
	int	row;

	free_config_textures(data);
	row = 0;
	while (row < data->config.map_height)
	{
		if (data->config.map[row])
			free(data->config.map[row]);
		row++;
	}
}

int	check_collision(t_data *data, int map_x, int map_y)
{
	if (map_x >= 0 && map_x < data->config.map_width
		&& map_y >= 0 && map_y < data->config.map_height
		&& data->config.map[map_y][map_x] != '1')
		return (0);
	return (1);
}
