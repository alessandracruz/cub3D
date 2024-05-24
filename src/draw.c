/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:26:01 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/24 14:14:53 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ver_line(t_data *data, t_lmap *lmap, t_line  line)
{
	int	index;
/*  	int	color; */

	index = -1;
/*  	color = 0x00d9742b;
	if (lmap->side)
		color = 0x0094450c; */
	while (++index < HEIGHT)
	{
 		int tex_y = (int)lmap->tex_pos & (TEX_SIZE - 1);
		lmap->tex_pos += lmap->step;
  		if (index < line.start)
			data->img.addr[index * WIDTH + lmap->x] = data->map.ceiling;
		else if (index <= line.end)
			data->img.addr[index * WIDTH + lmap->x] =  data->map.north.addr[TEX_SIZE * tex_y + lmap->tex_x];
		else
			data->img.addr[index * WIDTH + lmap->x] = data->map.floor;
	}
}
