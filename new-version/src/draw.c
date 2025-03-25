/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:34:34 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/25 01:39:48 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil_and_floor(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->config.height / 2)
	{
		x = 0;
		while (x < data->config.width)
		{
			mlx_put_pixel(data->img, x, y, data->config.ceil_color);
			mlx_put_pixel(data->img, x, data->config.height - y - 1,
				data->config.floor_color);
			x++;
		}
		y++;
	}
}

void	get_color(t_data_tex *var, mlx_texture_t *texture)
{
	var->color = ((uint32_t *)texture->pixels)[var->tex_y
		* texture->width + var->tex_x];
	var->bytes = (uint8_t *)&var->color;
	var->corrected_color = (var->bytes[0] << 24) | (var->bytes[1] << 16)
		| (var->bytes[2] << 8) | var->bytes[3];
}

void	turn_right(t_data *data, double rot_speed)
{
	data->player.angle += rot_speed;
}

void	turn_left(t_data *data, double rot_speed)
{
	data->player.angle -= rot_speed;
}
