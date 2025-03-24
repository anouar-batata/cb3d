/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouriga <alouriga@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 05:08:35 by alouriga          #+#    #+#             */
/*   Updated: 2025/03/24 09:12:55 by alouriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parce_helper(char *trimmed, t_vari **var, t_config **config,
				int *error_flag)
{
	if (*trimmed == '\0' && !(*var)->map_started)
	{
		return (1);
	}
	if (parce_helper_1(trimmed, var, config))
	{
		return (0);
	}
	else if (parce_helper_2(trimmed, var, config))
	{
		return (0);
	}
	else if (!(*var)->map_started && ft_strchr("01NSEW ", *trimmed))
	{
		(*var)->map_started = 1;
		*error_flag = 1;
		(*var)->map_line_start = (*var)->line_count;
	}
	else if (!(*error_flag))
	{
		ft_error_2("parce error\n", (*var)->fd);
	}
	return (0);
}

void	parce_first_arguments(t_vari **var, t_config **config, t_list **list)
{
	char		*trimmed;
	t_list		*list_copy;
	int			error_flag;

	error_flag = 0;
	list_copy = NULL;
	(*var)->line = get_next_line((*var)->fd);
	while ((*var)->line)
	{
		trimmed = ft_strtrim((*var)->line, " \t\n");
		if (parce_helper(trimmed, var, config, &error_flag))
		{
			(*var)->line = get_next_line((*var)->fd);
			continue ;
		}
		parce_first_arguments_2(*var, *config, list_copy, list);
		(*var)->line_count++;
		(*var)->line = get_next_line((*var)->fd);
	}
}

void	parse_cub_file(const char *filename, t_data *data, t_list *list)
{
	t_config	*config;
	t_vari		*var;

	first_parce(&var, filename);
	unit_variables(&config, &var, data);
	parce_first_arguments(&var, &config, &list);
	close(var->fd);
	if (list)
		var->map1 = list_to_array(list);
	if ((var->map1 && parse_1(var->map1, &config, 0, 0)))
		ft_error("parsing map");
	if (!config->flag_player)
		ft_error("parsing map");
	if (var->map_started)
		parse_map(config, data, var->map1,
			var->line_count - var->map_line_start);
	if (!config->no_texture || !config->so_texture || !config->we_texture
		||!config->ea_texture)
		ft_error("Missing required elements in .cub file");
}
