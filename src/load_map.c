/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:20:28 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/17 09:58:55 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_lmap(t_data */*data*/, t_lmap *lmap)
{
	lmap->posX = 22;
	lmap->posY = 12;
	lmap->dirX = -1;
	lmap->dirY = 0;
	lmap->planeX = 0;
	lmap->planeY = 0.66;
}

void	get_side_dists(t_lmap *lmap)
{
	if (lmap->rayDirX < 0)
	{
		lmap->stepX = -1;
		lmap->sideDistX = (lmap->posX - lmap->mapX) * lmap->deltaDistX;
	}
	else
	{
		lmap->stepX = 1;
		lmap->sideDistX = (lmap->mapX + 1.0 - lmap->posX) * lmap->deltaDistX;
	}
	if (lmap->rayDirY < 0)
	{
		lmap->stepY = -1;
		lmap->sideDistY = (lmap->posY - lmap->mapY) * lmap->deltaDistY;
	}
	else
	{
		lmap->stepY = 1;
		lmap->sideDistY = (lmap->mapY + 1.0 - lmap->posY) * lmap->deltaDistY;
	}
}

void	get_delta_dists(t_lmap *lmap)
{
	if (!lmap->rayDirX)
		lmap->deltaDistX = INT_MAX;
	else
		lmap->deltaDistX = fabs(1 / lmap->rayDirX);
	if (!lmap->rayDirY)
		lmap->deltaDistY = INT_MAX;
	else
		lmap->deltaDistY = fabs(1 / lmap->rayDirY);
}

int	get_line_height(t_data *data, t_lmap *lmap)
{
	int		hit;
	double	perp_wall_dist;

	hit = 0;
	while (hit == 0)
	{
		if (lmap->sideDistX < lmap->sideDistY)
		{
			lmap->sideDistX += lmap->deltaDistX;
			lmap->mapX += lmap->stepX;
			lmap->side = 0;
		}
		else
		{
			lmap->sideDistY += lmap->deltaDistY;
			lmap->mapY += lmap->stepY;
			lmap->side = 1;
		}
		if (data->map.grid[lmap->mapX][lmap->mapY] == '1')
			hit = 1;
	}
	if (lmap->side == 0)
		perp_wall_dist = (lmap->sideDistX - lmap->deltaDistX);
	else
		perp_wall_dist = (lmap->sideDistY - lmap->deltaDistY);
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
		data->lmap.cameraX = 2 * data->lmap.x / (double)WIDTH - 1;
		data->lmap.rayDirX = data->lmap.dirX + data->lmap.planeX * data->lmap.cameraX;
		data->lmap.rayDirY = data->lmap.dirY + data->lmap.planeY * data->lmap.cameraX;
		data->lmap.mapX = (int)data->lmap.posX;
		data->lmap.mapY = (int)data->lmap.posY;
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
