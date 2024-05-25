/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:24:16 by acastilh          #+#    #+#             */
/*   Updated: 2024/05/23 22:38:43 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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
*/

#include "cub3d.h"

void load_texture(void *mlx, t_texture *texture, char *path) {
    texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
    if (!texture->img) {
        printf("Error loading texture: %s\n", path);
        exit(1);
    }
    texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
    if (!texture->data) {
        printf("Error getting data address for texture: %s\n", path);
        exit(1);
    }
}

void init_textures(t_data *data) {
    load_texture(data->mlx, &data->textures[0], data->map.north);
    load_texture(data->mlx, &data->textures[1], data->map.south);
    load_texture(data->mlx, &data->textures[2], data->map.west);
    load_texture(data->mlx, &data->textures[3], data->map.east);
}

bool process_texture_line(char *line, t_data *data, t_error *error) {
    if (strncmp(line, "NO ", 3) == 0)
        strncpy(data->map.north, trim_spaces(&line[3]), TEX_PATH_LEN);
    else if (strncmp(line, "SO ", 3) == 0)
        strncpy(data->map.south, trim_spaces(&line[3]), TEX_PATH_LEN);
    else if (strncmp(line, "WE ", 3) == 0)
        strncpy(data->map.west, trim_spaces(&line[3]), TEX_PATH_LEN);
    else if (strncmp(line, "EA ", 3) == 0)
        strncpy(data->map.east, trim_spaces(&line[3]), TEX_PATH_LEN);
    else {
        set_error(error, "Invalid texture identifier", ERROR_UNKNOWN_IDENTIFIER);
        return false;
    }
    return true;
}
