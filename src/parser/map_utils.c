/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:11:45 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/19 23:39:53 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_map_lines(int fd)
{
	int		line_count;
	char	*line;

	line_count = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line))
		{
			line_count++;
		}
		free(line);
	}
	return (line_count);
}

void	free_map_grid(char ***grid, int line_count)
{
	int	j;

	j = 0;
	while (j < line_count)
	{
		free((*grid)[j]);
		j++;
	}
	free(*grid);
	*grid = NULL;
}

bool	fill_map_grid(int fd, char ***grid, int line_count, t_error *error)
{
	char	*line;
	int		i;

	i = 0;
	while (i < line_count && (line = get_next_line(fd)))
	{
		(*grid)[i++] = line;
	}
	if (i < line_count)
	{
		set_error(error, "Failed to read all map lines", ERROR_READ);
		free_map_grid(grid, i);
		return (false);
	}
	return (true);
}

bool	process_map_line(t_data *data, int fd, t_error *error)
{
	char	*line;
	int		i;

	data->map.line_count = count_map_lines(fd);
	if (data->map.line_count <= 0)
	{
		set_error(error, "Invalid or empty map", ERROR_EMPTY_MAP);
		return (false);
	}
	data->map.grid = (char **)malloc(sizeof(char *) * data->map.line_count);
	if (!data->map.grid)
	{
		set_error(error, "Failed to allocate memory for map grid",
			ERROR_MEMORY);
		return (false);
	}
	i = 0;
	while (i < data->map.line_count)
	{
		line = get_next_line(fd);
		if (line)
		{
			data->map.grid[i] = line;
			i++;
		}
		else
		{
			free_map_grid(&(data->map.grid), i);
			set_error(error, "Failed to read all map lines", ERROR_READ);
			return (false);
		}
	}
	return (true);
}
