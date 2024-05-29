/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:26:01 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/29 13:14:46 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ver_line(t_data *data, t_lmap *lmap, t_line  line)
{
	int	index;

	index = -1;
	while (++index < HEIGHT)
	{
 		lmap->tex[Y] = (int)lmap->tex_pos & (data->map.tex[0].h - 1);
		lmap->tex_pos += (lmap->tex_step);
  		if (index < line.start)
			data->img.addr[index * WIDTH + lmap->x] = data->map.ceiling;
		else if (index < line.end)
			data->img.addr[index * WIDTH + lmap->x] =  data->map.tex[0].addr[data->map.tex[0].h * lmap->tex[Y] + lmap->tex[X]];
		else
			data->img.addr[index * WIDTH + lmap->x] = data->map.floor;
	}
}
