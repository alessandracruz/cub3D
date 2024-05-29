/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:20:28 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/29 10:57:34 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_side_dists(t_lmap *lmap)
{
	if (lmap->raydir[X] < 0)
	{
		lmap->step[X] = -1;
		lmap->side_dist[X] = (lmap->pos[X] - lmap->map[X]) * lmap->delta_dist[X];
	}
	else
	{
		lmap->step[X] = 1;
		lmap->side_dist[X] = (lmap->map[X] + 1.0 - lmap->pos[X])
			* lmap->delta_dist[X];
	}
	if (lmap->raydir[Y] < 0)
	{
		lmap->step[Y] = -1;
		lmap->side_dist[Y] = (lmap->pos[Y] - lmap->map[Y]) * lmap->delta_dist[Y];
	}
	else
	{
		lmap->step[Y] = 1;
		lmap->side_dist[Y] = (lmap->map[Y] + 1.0 - lmap->pos[Y])
			* lmap->delta_dist[Y];
	}
}

void	get_delta_dists(t_lmap *lmap)
{
	if (!lmap->raydir[X])
		lmap->delta_dist[X] = 1e30;
	else
		lmap->delta_dist[X] = fabs(1 / lmap->raydir[X]);
	if (!lmap->raydir[Y])
		lmap->delta_dist[Y] = 1e30;
	else
		lmap->delta_dist[Y] = fabs(1 / lmap->raydir[Y]);
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
	if (!lmap->side)
		lmap->perp_wall_dist = (lmap->side_dist[X] - lmap->delta_dist[X]);
	else
		lmap->perp_wall_dist = (lmap->side_dist[Y] - lmap->delta_dist[Y]);
	return ((int)(HEIGHT / lmap->perp_wall_dist));
}

void	load_map(t_data *data)
{
	int		draw_end;
	int		draw_start;
	int		line_height;

	data->lmap.x = -1;
	while (++data->lmap.x < WIDTH)
	{
		data->lmap.camera_x = 2 * data->lmap.x / (double)WIDTH - 1;
		data->lmap.raydir[X] = data->lmap.dir[X] + data->lmap.plane[X]
			* data->lmap.camera_x;
		data->lmap.raydir[Y] = data->lmap.dir[Y] + data->lmap.plane[Y]
			* data->lmap.camera_x;
		data->lmap.map[X] = (int)data->lmap.pos[X];
		data->lmap.map[Y] = (int)data->lmap.pos[Y];
		get_delta_dists(&data->lmap);
		get_side_dists(&data->lmap);
		line_height = get_line_height(data, &data->lmap);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		double wall_x;
		
		if (!data->lmap.side)
			wall_x = data->lmap.pos[Y] + data->lmap.perp_wall_dist * data->lmap.raydir[Y];
		else
			wall_x = data->lmap.pos[X] + data->lmap.perp_wall_dist * data->lmap.raydir[X];
		wall_x -= floor(wall_x);
		
		data->lmap.tex[X] = (int)(wall_x * (double)data->map.tex[0].w);

		if ((!data->lmap.side && data->lmap.raydir[X] > 0) || (data->lmap.side && data->lmap.raydir[Y] < 0))
			data->lmap.tex[X] = data->map.tex[0].w - data->lmap.tex[X] - 1;

		data->lmap.tex_step = 1.0 * data->map.tex[0].h / line_height;
		data->lmap.tex_pos = (-HEIGHT / 2 + line_height / 2) * data->lmap.tex_step;
		draw_ver_line(data, &data->lmap, (t_line){draw_start, draw_end});
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
}
