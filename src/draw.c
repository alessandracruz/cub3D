/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:26:01 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/23 22:11:03 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	draw_ver_line(t_data *data, t_lmap *lmap, t_line line)
{
	int	index;
	int	color;

	index = 0;
	color = 0x00d9742b;
	if (lmap->side)
		color = 0x0094450c;
	while (index < line.start)
		mlx_pixel_put(data->mlx, data->win, lmap->x, index++, data->map.ceiling);
	while (index < HEIGHT && index <= line.end)
		mlx_pixel_put(data->mlx, data->win, lmap->x, index++, color);
	while (index < HEIGHT)
		mlx_pixel_put(data->mlx, data->win, lmap->x, index++, data->map.floor);
}
*/

void draw_ver_line(t_data *data, t_lmap *lmap, t_line line) {
    t_texture texture = data->textures[lmap->side];
    int tex_x = (int)(lmap->wall_x * (double)(texture.width));
    if (lmap->side == 0 && lmap->raydir_x > 0) tex_x = texture.width - tex_x - 1;
    if (lmap->side == 1 && lmap->raydir_y < 0) tex_x = texture.width - tex_x - 1;

    for (int y = line.start; y < line.end; y++) {
        int tex_y = (((y * 2 - HEIGHT + lmap->line_height) * texture.height) / lmap->line_height) / 2;
        unsigned int color = texture.data[tex_y * texture.width + tex_x];
        data->addr[y * data->line_length / 4 + lmap->x] = color;
    }
}



