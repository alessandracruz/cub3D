/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:36:56 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/04 23:48:51 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_configuration_line(char *trimmed_line, t_config *config)
{
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line,
			"SO ", 3) == 0 || ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0)
	{
		if (!parse_texture_line(trimmed_line, &config->textures))
		{
			config->parse_error = ERROR_TEXTURE;
		}
	}
	else if (ft_strncmp(trimmed_line, "F ", 2) == 0 || ft_strncmp(trimmed_line,
			"C ", 2) == 0)
	{
		if (!parse_color_line(trimmed_line, &config->colors))
		{
			config->parse_error = ERROR_COLOR;
		}
	}
	update_loaded_flags(config);
}
