/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:34:34 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/24 11:58:11 by bzinedda         ###   ########.fr       */
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
