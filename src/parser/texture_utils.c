/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:24:16 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 08:20:27 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	process_texture(const char *path, t_img *tex, t_data *data,
	t_error *error)
{
	ft_strncpy(tex->path, path, TEX_PATH_LEN);
	tex->ptr = mlx_xpm_file_to_image(data->mlx, tex->path, &tex->w, &tex->h);
	if (!tex->ptr)
	{
		set_error(error, "Invalid texture path", ERROR_INVALID_PATH);
		return (false);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->ptr, &tex->bpp,
			&tex->size_line, &tex->endian);
	return (true);
}

bool	process_texture_line(char *line, t_data *data, t_error *error)
{
	bool		check;
	const char	*path = trim_spaces(line + 2);

	if (!path)
	{
		set_error(error, "Invalid texture path", ERROR_INVALID_PATH);
		return (false);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
		check = process_texture(path, &data->map.tex[0], data, error);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		check = process_texture(path, &data->map.tex[1], data, error);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		check = process_texture(path, &data->map.tex[2], data, error);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		check = process_texture(path, &data->map.tex[3], data, error);
	else
	{
		set_error(error, "Unknown texture identifier",
			ERROR_UNKNOWN_IDENTIFIER);
		return (false);
	}
	return (check);
}
