/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:07:56 by acastilh          #+#    #+#             */
/*   Updated: 2024/05/04 11:35:34 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool validate_map_search_line(char **map, t_point size, t_point cur)
{
	return ((cur.x > 0 && !ft_strchr("1 ", map[cur.y][cur.x - 1]))
			|| !ft_strchr("1 ", map[cur.y][cur.x])
			|| (cur.x < size.x && !ft_strchr("1 ", map[cur.y][cur.x + 1])));
}

int validate_map_search(char **map, t_point size, t_point cur)
{
	int errors;

	errors = 0;
	if (cur.y < 0 || cur.y > size.y || cur.x < 0 || cur.x > size.x || map[cur.y][cur.x] != ' ')
		return 0;
	if ((cur.y > 0 && validate_map_search_line(map, size, (t_point){cur.x, cur.y - 1}))
			|| validate_map_search_line(map, size, (t_point){cur.x, cur.y})
			|| (cur.y < size.y && validate_map_search_line(map, size, (t_point){cur.x, cur.y + 1})))
		errors++;
	map[cur.y][cur.x] = '1';
	errors += validate_map_search(map, size, (t_point){cur.x - 1, cur.y});
	errors += validate_map_search(map, size, (t_point){cur.x + 1, cur.y});
	errors += validate_map_search(map, size, (t_point){cur.x, cur.y - 1});
	errors += validate_map_search(map, size, (t_point){cur.x, cur.y + 1});
	return (errors);
}

bool	validate_map(char **map, t_error * error)
{
	int y;
	int x;
	
	y = -1;
	while (map[++y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if ((y == 0 && !(map[y][x] == '1' || map[y][x] == ' '))
					|| (!map[y + 1] && !(map[y][x] == '1' || map[y][x] == ' '))
					|| (x == 0 && !(map[y][x] == '1' || map[y][x] == ' '))
					|| (!map[y][x + 1] && !(map[y][x] == '1' || map[y][x] == ' ')))
				return(set_error(error, "Map must be closed", ERROR_INVALID_MAP), ft_free_arrays(map), false);
			x++;
		}
	}
	int size_y = y - 1;
	int size_x = ft_strlen(map[0]) - 2;
	
	y = -1;
	int errors = 0;
 	while (map[++y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (map[y][x] == ' ')
				errors += validate_map_search(map, (t_point){size_x, size_y}, (t_point){x, y});
			x++;
		}
	}
	return (ft_free_arrays(map), true);
}

bool	parse_config_file(char *file_path, t_data *data, t_error *error)
{
	int		fd;
	char	*line;

	data->map.grid = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		set_error(error, "Error opening file", ERROR_FILE_OPEN);
		return (false);
	}
	while ((line = get_next_line(fd)))
	{
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		{
			if (!process_texture_line(line, data, error))
				return (free(line), clean_up(data), false);
		}
		else if (*line == 'F' || *line == 'C')
		{
			if (!process_color_line(line, data, error))
				return (free(line), clean_up(data), false);
		}
		else if (*line != '\0' && *line != '\n')
			data->map.grid = add_str_in_array(data->map.grid, line);
		free(line);
	}
	close(fd);
	data->map.grid = fill_array_spaces(data->map.grid);
	validate_map(ft_arraydup(data->map.grid), error);
	return (true);
}