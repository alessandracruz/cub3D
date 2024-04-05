/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:35:44 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/04 17:13:58 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map_config(char *file_path, t_config *config)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Failed to open file %s\n", file_path);
		return (-1);
	}
	config->textures_loaded = false;
    config->colors_loaded = false;
    config->is_map_start = false;
	while ((line = get_next_line(fd)))
	{
		parse_line(line, config);
		free(line);
		if (config->parse_error != PARSE_OK)
		{
			print_parse_error(config->parse_error, line);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	if (config->map.height == 0 || config->map.width == 0)
	{
		config->parse_error = ERROR_MAP_EMPTY;
		print_parse_error(config->parse_error, NULL);
		close(fd);
		return (-1);
	}
	if (!validate_map(&config->map, config))
	{
		print_parse_error(config->parse_error, NULL);
		return (-1);
	}
	ft_printf("Map and settings parsed and validated successfully.\n");
	return (0);
}

void	print_parse_error(t_parse_error error_code, char *line)
{
	if (line == NULL)
		line = "Unknown file";
	if (error_code == ERROR_TEXTURE)
		ft_printf("Error: Failed to parse texture line: %s\n", line);
	else if (error_code == ERROR_COLOR)
		ft_printf("Error: Failed to parse color line: %s\n", line);
	else if (error_code == ERROR_MAP)
		ft_printf("Error: Failed to parse map line: %s\n", line);
	else if (error_code == ERROR_MEMORY)
		ft_printf("Error: Memory allocation failed.\n");
	else if (error_code == ERROR_INVALID_CHAR)
		ft_printf("Error: Invalid character in map.\n");
	else if (error_code == ERROR_MISSING_PLAYER)
		ft_printf("Error: Missing player starting position.\n");
	else if (error_code == ERROR_OPEN_WALL)
		ft_printf("Error: Map is not surrounded by walls.\n");
	else if (error_code == ERROR_MULTIPLE_PLAYERS)
		ft_printf("Error: Multiple player starting positions found.\n");
	else if (error_code == ERROR_MAP_EMPTY)
		ft_printf("Error: Map is empty.\n");
	else
		ft_printf("Error: Unknown parsing error.\n");
}
