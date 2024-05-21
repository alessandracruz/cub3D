/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:20:28 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/21 12:54:38 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_side_dists(t_lmap *lmap)
{
	if (lmap->raydir_x < 0)
	{
		lmap->step_x = -1;
		lmap->side_dist_x = (lmap->pos_x - lmap->map_x) * lmap->delta_dist_x;
	}
	else
	{
		lmap->step_x = 1;
		lmap->side_dist_x = (lmap->map_x + 1.0 - lmap->pos_x)
			* lmap->delta_dist_x;
	}
	if (lmap->raydir_y < 0)
	{
		lmap->step_y = -1;
		lmap->side_dist_y = (lmap->pos_y - lmap->map_y) * lmap->delta_dist_y;
	}
	else
	{
		lmap->step_y = 1;
		lmap->side_dist_y = (lmap->map_y + 1.0 - lmap->pos_y)
			* lmap->delta_dist_y;
	}
}

void	get_delta_dists(t_lmap *lmap)
{
	if (!lmap->raydir_x)
		lmap->delta_dist_x = INT_MAX;
	else
		lmap->delta_dist_x = fabs(1 / lmap->raydir_x);
	if (!lmap->raydir_y)
		lmap->delta_dist_y = INT_MAX;
	else
		lmap->delta_dist_y = fabs(1 / lmap->raydir_y);
}

int	get_line_height(t_data *data, t_lmap *lmap)
{
	int		hit;
	double	perp_wall_dist;

	hit = 0;
	while (!hit)
	{
		if (lmap->side_dist_x < lmap->side_dist_y)
		{
			lmap->side_dist_x += lmap->delta_dist_x;
			lmap->map_x += lmap->step_x;
			lmap->side = 0;
		}
		else
		{
			lmap->side_dist_y += lmap->delta_dist_y;
			lmap->map_y += lmap->step_y;
			lmap->side = 1;
		}
		if (data->map.grid[lmap->map_x][lmap->map_y] == '1')
			hit = 1;
	}
	if (!lmap->side)
		perp_wall_dist = (lmap->side_dist_x - lmap->delta_dist_x);
	else
		perp_wall_dist = (lmap->side_dist_y - lmap->delta_dist_y);
	return ((int)(HEIGHT / perp_wall_dist));
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
		data->lmap.raydir_x = data->lmap.dir_x + data->lmap.plane_x
			* data->lmap.camera_x;
		data->lmap.raydir_y = data->lmap.dir_y + data->lmap.plane_y
			* data->lmap.camera_x;
		data->lmap.map_x = (int)data->lmap.pos_x;
		data->lmap.map_y = (int)data->lmap.pos_y;
		get_delta_dists(&data->lmap);
		get_side_dists(&data->lmap);
		line_height = get_line_height(data, &data->lmap);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		draw_ver_line(data, &data->lmap, (t_line){draw_start, draw_end});
	}
}
