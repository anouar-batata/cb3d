#include "cub3d.h"

void ft_error(const char *str)
{
	smart_free();
	printf("Error\n");
	printf("%s", str);
	// fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
	exit(1);
}

void load_textures(t_data *data)
{
	data->no_tex = mlx_load_png(data->config.no_texture);
	if (!data->no_tex)
		ft_error("Failed to load north texture");
	data->so_tex = mlx_load_png(data->config.so_texture); // Free this
	if (!data->so_tex)
	{
		mlx_load_png(data->config.no_texture);
		ft_error("Failed to load south texture");
	}
	data->we_tex = mlx_load_png(data->config.we_texture);
	if (!data->we_tex)
	{
		mlx_delete_texture(data->no_tex);
		mlx_delete_texture(data->so_tex);
		ft_error("Failed to load west texture");
	}
	data->ea_tex = mlx_load_png(data->config.ea_texture);
	if(!data->ea_tex)
	{
		mlx_delete_texture(data->no_tex);
		mlx_delete_texture(data->so_tex);
		mlx_delete_texture(data->we_tex);
		ft_error("Failed to load east texture");
	}
}

void free_config(t_data *data) {
	if (data->config.ea_texture) free(data->config.ea_texture);
	if (data->config.we_texture) free(data->config.we_texture);
	if (data->config.no_texture) free(data->config.no_texture);
	if (data->config.so_texture) free(data->config.so_texture);
	int row;

	row = 0;
	while (row < data->config.map_height) {
		if (data->config.map[row]) free(data->config.map[row]);
		row++;
	}
}

void free_textures(t_data *data)
{
	// free_config(data);

	if (data->no_tex) mlx_delete_texture(data->no_tex);
	if (data->so_tex) mlx_delete_texture(data->so_tex);
	if (data->we_tex) mlx_delete_texture(data->we_tex);
	if (data->ea_tex) mlx_delete_texture(data->ea_tex);
}

double	to_radian(int value)
{
	return (value  * M_PI / 180.0);
}