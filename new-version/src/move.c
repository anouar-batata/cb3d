/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:35:07 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/24 11:55:23 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_data *data, double move_speed)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = data->player.x + cos(data->player.angle) * move_speed;
	new_y = data->player.y + sin(data->player.angle) * move_speed;
	map_x = (int)(new_x / TILE_UNIT);
	map_y = (int)(new_y / TILE_UNIT);
	if (!check_collision(data, map_x, map_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_right(t_data *data, double move_speed)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = data->player.x + cos(data->player.angle + M_PI / 2) * move_speed;
	new_y = data->player.y + sin(data->player.angle + M_PI / 2) * move_speed;
	map_x = (int)(new_x / TILE_UNIT);
	map_y = (int)(new_y / TILE_UNIT);
	if (!check_collision(data, map_x, map_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_left(t_data *data, double move_speed)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = data->player.x + cos(data->player.angle - M_PI / 2) * move_speed;
	new_y = data->player.y + sin(data->player.angle - M_PI / 2) * move_speed;
	map_x = (int)(new_x / TILE_UNIT);
	map_y = (int)(new_y / TILE_UNIT);
	if (!check_collision(data, map_x, map_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_backward(t_data *data, double move_speed)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = data->player.x - cos(data->player.angle) * move_speed;
	new_y = data->player.y - sin(data->player.angle) * move_speed;
	map_x = (int)(new_x / TILE_UNIT);
	map_y = (int)(new_y / TILE_UNIT);
	if (!check_collision(data, map_x, map_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}
