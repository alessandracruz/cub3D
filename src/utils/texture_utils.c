/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:48 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/04 18:31:30 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_textures_loaded(t_texture *textures)
{
	return (textures->north[0] != '\0' && textures->south[0] != '\0'
		&& textures->west[0] != '\0' && textures->east[0] != '\0');
}

bool	validate_texture(char *path)
{
	int	fd;

	if (path == NULL || path[0] == '\0')
	{
		printf("Texture path is empty.\n");
		return (false);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Texture file does not exist or cannot be opened: %s\n", path);
		return (false);
	}
	close(fd);
    ft_printf("Texture validated successfully: %s\n", path);
	return (true);
}
