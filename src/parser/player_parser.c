/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:05:52 by matlopes          #+#    #+#             */
/*   Updated: 2024/06/01 10:06:51 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_dir(t_data *data, t_lmap *lmap, char **map)
{
	lmap->dir[X] = -1;
	lmap->dir[Y] = 0;
	lmap->plane[X] = 0;
	lmap->plane[Y] = 0.66;
	if (map[data->map.y][data->map.x] == 'W')
	{
		lmap->dir[X] = 0;
		lmap->dir[Y] = -1;
		lmap->plane[X] = -0.66;
		lmap->plane[Y] = 0;
	}
	if (map[data->map.y][data->map.x] == 'E')
	{
		lmap->dir[X] = 0;
		lmap->dir[Y] = 1;
		lmap->plane[X] = 0.66;
		lmap->plane[Y] = 0;
	}
	if (map[data->map.y][data->map.x] == 'S')
	{
		lmap->dir[X] = 1;
		lmap->dir[Y] = 0;
		lmap->plane[X] = 0;
		lmap->plane[Y] = -0.66;
	}
}

bool	get_player_pos_helper(t_data *data, char **map, t_error *error)
{
	data->map.x = -1;
	while (map[data->map.y][++data->map.x])
	{
		if (map[data->map.y][data->map.x] == 'N'
				|| map[data->map.y][data->map.x] == 'S'
				|| map[data->map.y][data->map.x] == 'E'
				|| map[data->map.y][data->map.x] == 'W')
		{
			if (data->map.p_check)
				return (set_error(error,
						"Map must contain only one player",
						ERROR_MULTIPLE_PLAYERS));
			data->lmap.pos[Y] = data->map.x + 0.5;
			data->lmap.pos[X] = data->map.y + 0.5;
			get_player_dir(data, &data->lmap, map);
			map[data->map.y][data->map.x] = '0';
			data->map.p_check = 1;
		}
	}
	return (true);
}

bool	get_player_pos(t_data *data, char **map, t_error *error)
{
	data->map.y = -1;
	data->map.p_check = 0;
	while (map[++data->map.y])
	{
		if (!get_player_pos_helper(data, map, error))
			return (false);
	}
	if (!data->map.p_check)
		return (set_error(error, "Map must contain a player",
				ERROR_INVALID_MAP));
	return (true);
}
