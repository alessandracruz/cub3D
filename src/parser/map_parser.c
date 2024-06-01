/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:07:56 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 08:23:35 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_dir(t_data *data, t_lmap *lmap, char **map)
{
	lmap->dir[X] = -1;
	lmap->dir[Y] = 0;
	lmap->plane[X] = 0;
	lmap->plane[Y] = 0.66;
	if (map[data->y][data->x] == 'W')
	{
		lmap->dir[X] = 0;
		lmap->dir[Y] = -1;
		lmap->plane[X] = -0.66;
		lmap->plane[Y] = 0;
	}
	if (map[data->y][data->x] == 'E')
	{
		lmap->dir[X] = 0;
		lmap->dir[Y] = 1;
		lmap->plane[X] = 0.66;
		lmap->plane[Y] = 0;
	}
	if (map[data->y][data->x] == 'S')
	{
		lmap->dir[X] = 1;
		lmap->dir[Y] = 0;
		lmap->plane[X] = 0;
		lmap->plane[Y] = -0.66;
	}
}

bool	get_player_pos(t_data *data, char **map, t_error *error)
{
	int	player_check;

	data->y = -1;
	player_check = 0;
	while (map[++data->y])
	{
		data->x = -1;
		while (map[data->y][++data->x])
		{
			if (map[data->y][data->x] == 'N' || map[data->y][data->x] == 'S'
					|| map[data->y][data->x] == 'E' || map[data->y][data->x] == 'W')
			{
				if (player_check)
					return (set_error(error, "Error opening file",
							ERROR_FILE_OPEN), false);
				data->lmap.pos[Y] = data->x + 0.5;
				data->lmap.pos[X] = data->y + 0.5;
				get_player_dir(data, &data->lmap, map);
				map[data->y][data->x] = '0';
				player_check = 1;
			}
		}
	}
	return (true);
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
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
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
	get_player_pos(data, data->map.grid, error);
	return (validate_map(ft_arraydup(data->map.grid), error));
}
