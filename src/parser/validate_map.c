/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:29:25 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/05 00:31:22 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_map(t_map *map, t_config *config)
{
	ft_printf("Starting map validation.\n");
	if (!validate_map_chars(map, config))
	{
		config->parse_error = ERROR_INVALID_CHAR;
		return (false);
	}
	if (!validate_player_start(map, config))
	{
		config->parse_error = ERROR_MISSING_PLAYER;
		return (false);
	}
	if (!validate_walls_closed(map, config))
	{
		config->parse_error = ERROR_OPEN_WALL;
		return (false);
	}
	ft_printf("Map validation completed.\n");
	return (true);
}

bool	validate_map_chars(t_map *map, t_config *config)
{
	int		i;
	int		j;
	char	current;
	bool	has_valid_content;

	has_valid_content = false;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			current = map->grid[i][j];
            ft_printf("Checking position [%d, %d] with char '%c'\n", i, j, current);
			if (current == ' ' || current == '0' || current == '1'
				|| ft_strchr("NSEW", current))
			{
				if (current != ' ')
				{
					has_valid_content = true;
				}
			}
			else
			{
                ft_printf("Invalid character detected at [%d, %d]: %c\n", i, j, current);
				config->parse_error = ERROR_INVALID_CHAR;
				return (false);
			}
			j++;
		}
		i++;
	}
	if (!has_valid_content)
	{
		ft_printf("Map is empty or contains only spaces.\n");
        config->parse_error = ERROR_MAP_EMPTY;
		return (false);
	}
	return (true);
}

bool	validate_player_start(t_map *map, t_config *config)
{
	int		i;
	int		j;
	int		player_count;
	char	current;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			current = map->grid[i][j];
			if (ft_strchr("NSEW", current))
			{
				player_count++;
				set_player_position(config, j, i, current);
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
	{
		config->parse_error = ERROR_MISSING_PLAYER;
		return (false);
	}
	else if (player_count > 1)
	{
		config->parse_error = ERROR_MULTIPLE_PLAYERS;
		return (false);
	}
	return (true);
}

bool	validate_walls_closed(t_map *map, t_config *config)
{
	int	j;
	int	i;

	j = 0;
	while (j < map->width)
	{
		if (map->grid[0][j] != '1' || map->grid[map->height - 1][j] != '1')
		{
			config->parse_error = ERROR_OPEN_WALL;
			return (false);
		}
		j++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
		{
			config->parse_error = ERROR_OPEN_WALL;
			return (false);
		}
		i++;
	}
	return (true);
}
