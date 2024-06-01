/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:20:28 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/31 13:18:58 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_tex_values(t_data *data, t_lmap *lmap, int line_height)
{
	double	wall_x;

	wall_x = lmap->pos[1 - lmap->side] + lmap->perp_wall_dist
		* lmap->raydir[1 - lmap->side];
	wall_x -= floor(wall_x);
	if (lmap->side && lmap->raydir[Y] > 0)
		lmap->tex_type = EA;
	else if (lmap->side && lmap->raydir[Y] < 0)
		lmap->tex_type = WE;
	else if (!lmap->side && lmap->raydir[X] > 0)
		lmap->tex_type = SO;
	else if (!lmap->side && lmap->raydir[X] < 0)
		lmap->tex_type = NO;
	lmap->tex[X] = (int)(wall_x * (double)data->map.tex[lmap->tex_type].w);
	if ((!lmap->side && lmap->raydir[X] > 0)
		|| (lmap->side && lmap->raydir[Y] < 0))
		lmap->tex[X] = data->map.tex[lmap->tex_type].w
			- lmap->tex[X] - 1;
	lmap->tex_step = 1.0 * data->map.tex[lmap->tex_type].h / line_height;
	lmap->tex_pos = (-HEIGHT / 2 + line_height / 2)
		* lmap->tex_step;
}

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
		get_tex_values(data, &data->lmap, line_height);
		draw_ver_line(data, &data->lmap, (t_line){draw_start, draw_end});
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
}
