/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:07:56 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/20 17:04:39 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**fill_array_spaces(char **array)
{
	int		index;
	int 	length;
	char	**new_array;

	length = -1;
	index = -1;
	while (array[++index])
	{
		if ((int)ft_strlen(array[index]) > length)
			length = ft_strlen(array[index]);
	}
	new_array = malloc((ft_arraylen(array) + 1) * sizeof(char **));
	if (!new_array)
		return (NULL);
	index = -1;
	while (array[++index])
		new_array[index] = ft_strldup(array[index], length);
	new_array[index] = NULL;
	free(array);
	return (new_array);
}

bool	validate_map(t_data *data, t_error */* error */)
{
	int x;
	int y;
	
	x = -1;
	while (data->map.grid[++x])
	{
		y = 0;
		while (data->map.grid[x][y] && data->map.grid[x][y] != '\n')
		{
			if (x == 0 && !(data->map.grid[x][y] == '1' || data->map.grid[x][y] == ' '))
			{
				ft_printf("Error");
				exit(0);
			}
			if (!data->map.grid[x + 1] && !(data->map.grid[x][y] == '1' || data->map.grid[x][y] == ' '))
			{
				ft_printf("Error");
				exit(0);
			}
			if (y == 0 && !(data->map.grid[x][y] == '1' || data->map.grid[x][y] == ' '))
			{
				ft_printf("Error");
				exit(0);
			}
			if (!data->map.grid[x][y + 1] && !(data->map.grid[x][y] == '1' || data->map.grid[x][y] == ' '))
			{
				ft_printf("Error");
				exit(0);
			}
			ft_printf("%c", data->map.grid[x][y]);
			y++;
		}
		ft_printf("\n");
	}
	ft_printf("\n");
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
	while ((line = get_next_line(fd)))
	{
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		{
			if (!process_texture_line(line, data, error))
				return (free(line), false);
		}
		else if (*line == 'F' || *line == 'C')
		{
			if (!process_color_line(line, data, error))
				return (free(line), false);
		}
		else if (*line != '\0' && *line != '\n')
			data->map.grid = add_str_in_array(data->map.grid, line);
		if (!(*line != '\0' && *line != '\n'))
			free(line);
	}
	close(fd);
	data->map.grid = fill_array_spaces(data->map.grid);
	validate_map(data, error);
	return (true);
}