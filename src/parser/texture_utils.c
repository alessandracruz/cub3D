/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:24:16 by acastilh          #+#    #+#             */
/*   Updated: 2024/05/24 14:12:33 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	process_texture_line(char *line, t_data *data, t_error *error)
{
	const char	*path = trim_spaces(line + 2);
	int width;
	int height;

	if (!path)
	{
		set_error(error, "Invalid texture path", ERROR_INVALID_PATH);
		return (false);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		ft_strncpy(data->map.north.path, path, TEX_PATH_LEN);
		data->map.north.ptr = mlx_xpm_file_to_image(data->mlx, data->map.north.path, &width, &height);
		data->map.north.addr = (int *)mlx_get_data_addr(data->map.north.ptr, &data->map.north.bpp, &data->map.north.size_line, &data->map.north.endian);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
		ft_strncpy(data->map.south.path, path, TEX_PATH_LEN);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		ft_strncpy(data->map.west.path, path, TEX_PATH_LEN);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		ft_strncpy(data->map.east.path, path, TEX_PATH_LEN);
	else
	{
		set_error(error, "Unknown texture identifier",
			ERROR_UNKNOWN_IDENTIFIER);
		return (false);
	}
	return (true);
}
