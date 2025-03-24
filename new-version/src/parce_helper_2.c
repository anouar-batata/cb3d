/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:08:40 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/24 09:20:00 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_parce(t_vari **var, const char *filename)
{
	(*var) = smart_malloc(sizeof(t_vari));
	if (parce_name_file(filename, ft_strlen(filename)))
		ft_error("file name incorrect");
	(*var)->fd = open(filename, O_RDONLY);
	if ((*var)->fd < 0)
		ft_error("Cannot open .cub file");
}

void	parce_first_arguments_2(t_vari *var, t_config *config,
							t_list *list_copy, t_list **list)
{
	if (var->map_started)
	{
		if (!(config)->no_texture || !(config)->so_texture
			|| !(config)->we_texture
			|| !(config)->ea_texture || !(config)->ceil_color
			|| !(config)->floor_color)
			ft_error_2("Missing required elements in .cub file", (var)->fd);
		if (check_line((var)->line))
			ft_error_2("parsing map", (var)->fd);
		list_copy = ft_lstnew((var)->line);
		ft_lstadd_back(list, list_copy);
	}
}

int	parce_helper_1(char *trimmed, t_vari **var, t_config **config)
{
	if (!(*var)->map_started && ft_strncmp(trimmed, "NO ", 3) == 0
		&& !(*config)->no_texture)
	{
		(*var)->path_start = ft_strtrim(trimmed + 3, " \t\n");
		(*config)->no_texture = ft_strdup((*var)->path_start);
		return (1);
	}
	else if (!(*var)->map_started && ft_strncmp(trimmed, "SO ", 3) == 0
		&& !(*config)->so_texture)
	{
		(*var)->path_start = ft_strtrim(trimmed + 3, " \t\n");
		(*config)->so_texture = ft_strdup((*var)->path_start);
		return (1);
	}
	else if (!(*var)->map_started && ft_strncmp(trimmed, "WE ", 3) == 0
		&& !(*config)->we_texture)
	{
		(*var)->path_start = ft_strtrim(trimmed + 3, " \t\n");
		(*config)->we_texture = ft_strdup((*var)->path_start);
		return (1);
	}
	return (0);
}

int	parce_helper_2(char *trimmed, t_vari **var, t_config **config)
{
	if (!(*var)->map_started && ft_strncmp(trimmed, "EA ", 3) == 0
		&& !(*config)->ea_texture)
	{
		(*var)->path_start = ft_strtrim(trimmed + 3, " \t\n");
		(*config)->ea_texture = ft_strdup((*var)->path_start);
		return (1);
	}
	else if (!(*var)->map_started && ft_strncmp(trimmed, "F ", 2) == 0
		&& !(*config)->floor_color)
	{
		(*var)->color_str = ft_strtrim(trimmed + 2, " \t\n");
		(*config)->floor_color = parse_color((*var)->color_str, 0,
				0, (*var)->fd);
		return (1);
	}
	else if (!(*var)->map_started && ft_strncmp(trimmed, "C ", 2) == 0
		&& !(*config)->ceil_color)
	{
		(*var)->color_str = ft_strtrim(trimmed + 2, " \t\n");
		(*config)->ceil_color = parse_color((*var)->color_str,
				0, 0, (*var)->fd);
		return (1);
	}
	return (0);
}
