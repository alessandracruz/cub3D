/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:20:28 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/14 13:06:48 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_data *data)
{
	int	index;
	int	counter;

	index = -1;
	counter = -1;
	while (++index < WIDTH)
	{
		counter = -1;
		while (++counter < HEIGHT)
		{
			if (counter < HEIGHT / 2)
				mlx_pixel_put(data->mlx, data->win, index, counter, 0x0079abc7);
			else
				mlx_pixel_put(data->mlx, data->win, index, counter, 0x00107303);
		}
	}
}

void	draw_ver_line(t_data *data, t_lmap *lmap, t_line line)
{
	int	index;
	int	color;

	index = line.start;
	if (line.start < 0)
		index = 0;
	color = 0x00d9742b;
	if (lmap->side)
		color = 0x0094450c;
	while (index < HEIGHT && index <= line.end)
		mlx_pixel_put(data->mlx, data->win, lmap->x, index++, color);
}

void	init_lmap(t_data */*data*/, t_lmap *lmap)
{
	lmap->x = -1;
	lmap->posX = 4;
	lmap->posY = 13;
	lmap->dirX = 1;
	lmap->dirY = -0.5;
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
	t_lmap	lmap;
	int		draw_end;
	int		draw_start;
	int		line_height;

	init_lmap(data, &lmap);
	draw_background(data);
	while (++lmap.x < WIDTH)
	{
		lmap.cameraX = 2 * lmap.x / (double)WIDTH - 1;
		lmap.rayDirX = lmap.dirX + lmap.planeX * lmap.cameraX;
		lmap.rayDirY = lmap.dirY + lmap.planeY * lmap.cameraX;
		lmap.mapX = (int)lmap.posX;
		lmap.mapY = (int)lmap.posY;
		get_delta_dists(&lmap);
		get_side_dists(&lmap);
		line_height = get_line_height(data, &lmap);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		draw_ver_line(data, &lmap, (t_line){draw_start, draw_end});
	}
}
