/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:24:16 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/08 18:24:32 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	process_texture_line(char *line, t_data *data)
{
	const char *path = ft_strchr(line, ' ') + 1;
		// Pula o identificador e o espaço.
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		ft_strncpy(data->map.north, path, TEX_PATH_LEN);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		ft_strncpy(data->map.south, path, TEX_PATH_LEN);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		ft_strncpy(data->map.west, path, TEX_PATH_LEN);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		ft_strncpy(data->map.east, path, TEX_PATH_LEN);
	}
	else
	{
		return (false);
			// A linha não corresponde a um identificador de textura conhecido.
	}
	return (true); // Processamento bem-sucedido.
}
