/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:26:29 by matlopes          #+#    #+#             */
/*   Updated: 2024/06/01 09:47:26 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_map_search_line(char **map, t_point size, t_point cur)
{
	return ((cur.x > 0 && !ft_strchr("1 ", map[cur.y][cur.x - 1]))
			|| !ft_strchr("1 ", map[cur.y][cur.x])
			|| (cur.x < size.x && !ft_strchr("1 ", map[cur.y][cur.x + 1])));
}

int	validate_map_search(char **map, t_point size, t_point cur)
{
	int	errors;

	errors = 0;
	if (cur.y < 0 || cur.y > size.y || cur.x < 0 || cur.x > size.x
		|| map[cur.y][cur.x] != ' ')
		return (0);
	if ((cur.y > 0
			&& validate_map_search_line(map, size, (t_point){cur.x, cur.y - 1}))
			|| validate_map_search_line(map, size, (t_point){cur.x, cur.y})
			|| (cur.y < size.y && validate_map_search_line(map, size,
			(t_point){cur.x, cur.y + 1})))
		errors++;
	map[cur.y][cur.x] = '1';
	errors += validate_map_search(map, size, (t_point){cur.x - 1, cur.y});
	errors += validate_map_search(map, size, (t_point){cur.x + 1, cur.y});
	errors += validate_map_search(map, size, (t_point){cur.x, cur.y - 1});
	errors += validate_map_search(map, size, (t_point){cur.x, cur.y + 1});
	return (errors);
}

int	validate_map_start_search(char **map, int map_height)
{
	int	y;
	int	x;
	int	size_y;
	int	size_x;
	int	errors;

	y = -1;
	errors = 0;
	size_y = map_height - 1;
	size_x = ft_strlen(map[0]) - 2;
	while (map[++y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (map[y][x] == ' ')
				errors += validate_map_search(map,
						(t_point){size_x, size_y}, (t_point){x, y});
			x++;
		}
	}
	return (errors);
}

bool	validate_map_helper(char **map, t_error *error, t_point pos)
{
	if (!is_valid_character(map[pos.y][pos.x]))
		return (set_error(error, "Map has a invalid character",
				ERROR_INVALID_MAP));
	if ((pos.y == 0 && !(map[pos.y][pos.x] == '1'
			|| map[pos.y][pos.x] == ' ')) || (!map[pos.y + 1]
		&& !(map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == ' '))
		|| (pos.x == 0 && !(map[pos.y][pos.x] == '1'
		|| map[pos.y][pos.x] == ' '))
		|| (!map[pos.y][pos.x + 1] && !(map[pos.y][pos.x] == '1'
		|| map[pos.y][pos.x] == ' ')))
		return (set_error(error, "Map must be closed",
				ERROR_INVALID_MAP));
	return (true);
}

bool	validate_map(char **map, t_error *error)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (!validate_map_helper(map, error, (t_point){x, y}))
			{
				ft_free_arrays(map);
				return (false);
			}
			x++;
		}
	}
	if (validate_map_start_search(map, y))
		return (set_error(error, "Map must be closed",
				ERROR_INVALID_MAP), ft_free_arrays(map), false);
	return (ft_free_arrays(map), true);
}
