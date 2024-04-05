/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:07:07 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/05 00:22:31 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_line(char *line, t_config *config) {
    char *trimmed_line = ft_strtrim(line, " \t\n");
    if (!trimmed_line) {
        config->parse_error = ERROR_MEMORY;
        return;
    }
	ft_printf("Before processing map line: Textures: %s, Colors: %s, Map Start: %s\n",
          config->textures_loaded ? "Loaded" : "Not Loaded",
          config->colors_loaded ? "Loaded" : "Not Loaded",
          config->is_map_start ? "Yes" : "No");

    // Corrigindo a chamada de ft_printf
    ft_printf("Processing line: '%s'. Map start: %s. Textures loaded: %s. Colors loaded: %s\n",
              trimmed_line,
              config->is_map_start ? "Yes" : "No",
              config->textures_loaded ? "Yes" : "No",
              config->colors_loaded ? "Yes" : "No");

    if (!config->is_map_start) {
        process_configuration_line(trimmed_line, config);
        if (config->textures_loaded && config->colors_loaded) {
            config->is_map_start = true;
            ft_printf("Map processing starts now.\n");
        }
    } else {
        if (!parse_map_line(trimmed_line, &config->map, config)) {
            config->parse_error = ERROR_MAP;
        }
    }

    free(trimmed_line);
}


void	update_loaded_flags(t_config *config)
{
	config->textures_loaded = check_textures_loaded(&config->textures);
	config->colors_loaded = check_colors_loaded(&config->colors);
	if (config->textures_loaded && config->colors_loaded)
	{
		config->is_map_start = true;
	}
}

bool	parse_texture_line(char *line, t_texture *textures)
{
	const char	*path_start;

	path_start = ft_strchr(line, ' ');
	if (!path_start)
		return (false);
	path_start = ft_strtrim(path_start, " \t");
	if (!path_start)
		return (false);
	if (ft_strncmp(line, "NO ", 3) == 0)
		ft_strlcpy(textures->north, path_start, TEX_PATH_LEN);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		ft_strlcpy(textures->south, path_start, TEX_PATH_LEN);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		ft_strlcpy(textures->west, path_start, TEX_PATH_LEN);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		ft_strlcpy(textures->east, path_start, TEX_PATH_LEN);
	else
		return (false);
	return (true);
}

bool	parse_color_line(char *line, t_color *colors)
{
	char	**rgb;
	char	*trimmed;

	int r, g, b;
	trimmed = ft_strtrim(line + 1, " \t");
	if (!trimmed)
		return (false);
	rgb = ft_split(trimmed, ',');
	free(trimmed);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_split(rgb);
		return (false);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	colors->floor = (line[0] == 'F') ? (r << 16 | g << 8 | b) : colors->floor;
	colors->ceiling = (line[0] == 'C') ? (r << 16 | g << 8 | b) : colors->ceiling;
	return (true);
}

bool	parse_map_line(char *line, t_map *map, t_config *config)
{
	char	**new_grid;
	int		i;
	size_t	new_line_length;
	int		j;

	new_grid = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
	{
		return (false);
	}
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	new_grid[i] = ft_strdup(line);
	if (!new_grid[i])
	{
		i--;
		while (i >= 0)
		{
			free(new_grid[i]);
			i--;
		}
		free(new_grid);
		return (false);
	}
	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E'
			|| line[j] == 'W')
		{
			ft_printf("Player starting position detected: %c at [%d, %d]\n",
				line[j], map->height, j);
			config->player.x = j; // Ajuste conforme seu modelo
			config->player.y = map->height;
			// Adicionar mais configurações conforme necessário
		}
		j++;
	}
	new_grid[map->height + 1] = NULL;
	if (map->grid != NULL)
	{
		free(map->grid);
	}
	map->grid = new_grid;
	map->height++;
	new_line_length = ft_strlen(line);
	map->width = (new_line_length > (size_t)map->width) ? (int)new_line_length : map->width;
	return (true);
}
