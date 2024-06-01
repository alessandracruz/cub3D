/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:07:56 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 10:15:02 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_config_file(t_data *data, t_error *error, int fd)
{
	char	*line;

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
	return (true);
}

bool	parse_config(char *file_path, t_data *data, t_error *error)
{
	int		fd;

	data->map.grid = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		set_error(error, "Error opening file", ERROR_FILE_OPEN);
		return (false);
	}
	if (!parse_config_file(data, error, fd))
		return (false);
	close(fd);
	data->map.grid = fill_array_spaces(data->map.grid);
	if (!get_player_pos(data, data->map.grid, error))
		return (false);
	return (validate_map(ft_arraydup(data->map.grid), error));
}
