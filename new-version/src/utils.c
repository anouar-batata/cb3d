/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:34:37 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/24 11:43:48 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_north_south(t_data *data)
{
	data->no_tex = mlx_load_png(data->config.no_texture);
	if (!data->no_tex)
		ft_error("Failed to load north texture");
	data->so_tex = mlx_load_png(data->config.so_texture);
	if (!data->so_tex)
	{
		mlx_delete_texture(data->no_tex);
		ft_error("Failed to load south texture");
	}
}

static void	load_west_east(t_data *data)
{
	data->we_tex = mlx_load_png(data->config.we_texture);
	if (!data->we_tex)
	{
		mlx_delete_texture(data->no_tex);
		mlx_delete_texture(data->so_tex);
		ft_error("Failed to load west texture");
	}
	data->ea_tex = mlx_load_png(data->config.ea_texture);
	if (!data->ea_tex)
	{
		mlx_delete_texture(data->no_tex);
		mlx_delete_texture(data->so_tex);
		mlx_delete_texture(data->we_tex);
		ft_error("Failed to load east texture");
	}
}

void	load_textures(t_data *data)
{
	load_north_south(data);
	load_west_east(data);
}

void	free_textures(t_data *data)
{
	if (data->no_tex)
		mlx_delete_texture(data->no_tex);
	if (data->so_tex)
		mlx_delete_texture(data->so_tex);
	if (data->we_tex)
		mlx_delete_texture(data->we_tex);
	if (data->ea_tex)
		mlx_delete_texture(data->ea_tex);
}
