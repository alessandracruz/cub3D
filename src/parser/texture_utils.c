/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:24:16 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/20 14:43:18 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	process_texture_line(char *line, t_data *data, t_error *error)
{
	const char	*path = trim_spaces(line + 2);

	if (!path)
	{
		set_error(error, "Invalid texture path", ERROR_INVALID_PATH);
		return (false);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
		ft_strncpy(data->map.north, path, TEX_PATH_LEN);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		ft_strncpy(data->map.south, path, TEX_PATH_LEN);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		ft_strncpy(data->map.west, path, TEX_PATH_LEN);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		ft_strncpy(data->map.east, path, TEX_PATH_LEN);
	else
	{
		set_error(error, "Unknown texture identifier",
			ERROR_UNKNOWN_IDENTIFIER);
		return (false);
	}
	return (true);
}