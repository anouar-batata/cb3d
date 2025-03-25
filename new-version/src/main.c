/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:34:58 by bzinedda          #+#    #+#             */
/*   Updated: 2025/03/25 01:41:25 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error("Usage: ./cub3d <map.cub>");
	parse_cub_file(argv[1], &data, NULL);
	data.mlx = mlx_init(data.config.width, data.config.height, "Cub3D", true);
	if (!data.mlx)
		ft_error("MLX initialization failed");
	load_textures(&data);
	data.img = mlx_new_image(data.mlx, data.config.width, data.config.height);
	if (!data.img || mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
	{
		mlx_terminate(data.mlx);
		ft_error("MLX image creation or display failed");
	}
	mlx_loop_hook(data.mlx, ft_render, &data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	free_textures(&data);
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);
	smart_free();
	return (EXIT_SUCCESS);
}
