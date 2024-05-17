/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:26:01 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/17 10:04:19 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ver_line(t_data *data, t_lmap *lmap, t_line line)
{
	int	index;
	int	color;

    index = 0;
	color = 0x00d9742b;
	if (lmap->side)
		color = 0x0094450c;
    while (index < line.start)
		mlx_pixel_put(data->mlx, data->win, lmap->x, index++, 0x0079abc7);
	while (index < HEIGHT && index <= line.end)
		mlx_pixel_put(data->mlx, data->win, lmap->x, index++, color);
	while (index < HEIGHT)
		mlx_pixel_put(data->mlx, data->win, lmap->x, index++, 0x00107303);

}