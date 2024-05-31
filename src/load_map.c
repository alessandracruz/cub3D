/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:20:28 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/31 11:45:03 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_line_height(t_data *data, t_lmap *lmap)
{
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (lmap->side_dist[X] < lmap->side_dist[Y])
		{
			lmap->side_dist[X] += lmap->delta_dist[X];
			lmap->map[X] += lmap->step[X];
			lmap->side = 0;
		}
		else
		{
			lmap->side_dist[Y] += lmap->delta_dist[Y];
			lmap->map[Y] += lmap->step[Y];
			lmap->side = 1;
		}
		if (data->map.grid[lmap->map[X]][lmap->map[Y]] == '1')
			hit = 1;
	}
	lmap->perp_wall_dist = (lmap->side_dist[lmap->side]
			- lmap->delta_dist[lmap->side]);
	return ((int)(HEIGHT / lmap->perp_wall_dist));
}

void	get_dists(t_lmap *lmap, int index)
{
	if (!lmap->raydir[index])
		lmap->delta_dist[index] = 1e30;
	else
		lmap->delta_dist[index] = fabs(1 / lmap->raydir[index]);
	lmap->map[index] = (int)lmap->pos[index];
	if (lmap->raydir[index] < 0)
	{
		lmap->step[index] = -1;
		lmap->side_dist[index] = (lmap->pos[index] - lmap->map[index])
			* lmap->delta_dist[index];
	}
	else
	{
		lmap->step[index] = 1;
		lmap->side_dist[index] = (lmap->map[index] + 1.0 - lmap->pos[index])
			* lmap->delta_dist[index];
	}
}

void	load_map_values(t_lmap *lmap)
{
	int	index;

	index = -1;
	lmap->camera_x = 2 * lmap->x / (double)WIDTH - 1;
	while (++index <= 1)
	{
		lmap->raydir[index] = lmap->dir[index] + lmap->plane[index]
			* lmap->camera_x;
		get_dists(lmap, index);
	}
}

void	load_map(t_data *data)
{
	int		tex_index;
	double	wall_x;
	int		draw_end;
	int		draw_start;
	int		line_height;

	data->lmap.x = -1;
	while (++data->lmap.x < WIDTH)
	{
		load_map_values(&data->lmap);
		line_height = get_line_height(data, &data->lmap);
		draw_start = -line_height / 2 + HEIGHT / 2;
		draw_end = line_height / 2 + HEIGHT / 2;
		wall_x = data->lmap.pos[1 - data->lmap.side] + data->lmap.perp_wall_dist
			* data->lmap.raydir[1 - data->lmap.side];
		wall_x -= floor(wall_x);

		if (data->lmap.side && data->lmap.raydir[Y] > 0)
			tex_index = EA;
		else if (data->lmap.side && data->lmap.raydir[Y] < 0)
			tex_index = WE;
		else if (!data->lmap.side && data->lmap.raydir[X] > 0)
			tex_index = SO;
		else if (!data->lmap.side && data->lmap.raydir[X] < 0)
			tex_index = NO;

		data->lmap.tex[X] = (int)(wall_x * (double)data->map.tex[tex_index].w);
		if ((!data->lmap.side && data->lmap.raydir[X] > 0)
			|| (data->lmap.side && data->lmap.raydir[Y] < 0))
			data->lmap.tex[X] = data->map.tex[tex_index].w - data->lmap.tex[X] - 1;
		data->lmap.tex_step = 1.0 * data->map.tex[tex_index].h / line_height;
		data->lmap.tex_pos = (-HEIGHT / 2 + line_height / 2)
			* data->lmap.tex_step;
		draw_ver_line(data, &data->lmap, (t_line){draw_start, draw_end}, tex_index);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
}
