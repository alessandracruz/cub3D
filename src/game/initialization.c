/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:54:25 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/04 16:56:13 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_player_direction(t_player *player, char orientation)
{
	player->dir_x = 0;
	player->dir_y = 0;
	if (orientation == 'N')
		player->dir_y = -1;
	else if (orientation == 'S')
		player->dir_y = 1;
	else if (orientation == 'E')
		player->dir_x = 1;
	else if (orientation == 'W')
		player->dir_x = -1;
}

void	set_player_position(t_config *config, int x, int y, char orientation)
{
	config->player.x = x;
	config->player.y = y;
	initialize_player_direction(&config->player, orientation);
}
