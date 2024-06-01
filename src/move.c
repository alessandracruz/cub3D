/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:37:37 by matlopes          #+#    #+#             */
/*   Updated: 2024/06/01 10:39:02 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_ver(t_data *data, int type)
{
	if (type == 1)
	{
		if (data->map.grid[(int)(data->lmap.pos[X] + data->lmap.dir[X]
				* MOV_SPEED)][(int)data->lmap.pos[Y]] == '0')
			data->lmap.pos[X] += data->lmap.dir[X] * MOV_SPEED;
		if (data->map.grid[(int)(data->lmap.pos[X])][(int)
				(data->lmap.pos[Y] + data->lmap.dir[Y] * MOV_SPEED)] == '0')
			data->lmap.pos[Y] += data->lmap.dir[Y] * MOV_SPEED;
	}
	else
	{
		if (data->map.grid[(int)(data->lmap.pos[X] - data->lmap.dir[X]
				* MOV_SPEED)][(int)data->lmap.pos[Y]] == '0')
			data->lmap.pos[X] -= data->lmap.dir[X] * MOV_SPEED;
		if (data->map.grid[(int)(data->lmap.pos[X])][(int)
				(data->lmap.pos[Y] - data->lmap.dir[Y] * MOV_SPEED)] == '0')
			data->lmap.pos[Y] -= data->lmap.dir[Y] * MOV_SPEED;
	}
	return (1);
}

int	move_hor(t_data *data, int type)
{
	if (type == 1)
	{
		if (data->map.grid[(int)(data->lmap.pos[X] + data->lmap.plane[X]
				* MOV_SPEED)][(int)data->lmap.pos[Y]] == '0')
			data->lmap.pos[X] += data->lmap.plane[X] * MOV_SPEED;
		if (data->map.grid[(int)(data->lmap.pos[X])][(int)
				(data->lmap.pos[Y] + data->lmap.plane[Y] * MOV_SPEED)] == '0')
			data->lmap.pos[Y] += data->lmap.plane[Y] * MOV_SPEED;
	}
	else
	{
		if (data->map.grid[(int)(data->lmap.pos[X] - data->lmap.plane[X]
				* MOV_SPEED)][(int)data->lmap.pos[Y]] == '0')
			data->lmap.pos[X] -= data->lmap.plane[X] * MOV_SPEED;
		if (data->map.grid[(int)(data->lmap.pos[X])][(int)
				(data->lmap.pos[Y] - data->lmap.plane[Y] * MOV_SPEED)] == '0')
			data->lmap.pos[Y] -= data->lmap.plane[Y] * MOV_SPEED;
	}
	return (1);
}

int	rotate(t_data *data, int type)
{
	double	old_dir[X];
	double	old_plane[X];

	old_dir[X] = data->lmap.dir[X];
	old_plane[X] = data->lmap.plane[X];
	data->lmap.dir[X] = data->lmap.dir[X] * cos(type * ROT_SPEED)
		- data->lmap.dir[Y] * sin(type * ROT_SPEED);
	data->lmap.dir[Y] = old_dir[X] * sin(type * ROT_SPEED)
		+ data->lmap.dir[Y] * cos(type * ROT_SPEED);
	data->lmap.plane[X] = data->lmap.plane[X] * cos(type * ROT_SPEED)
		- data->lmap.plane[Y] * sin(type * ROT_SPEED);
	data->lmap.plane[Y] = old_plane[X] * sin(type * ROT_SPEED)
		+ data->lmap.plane[Y] * cos(type * ROT_SPEED);
	return (1);
}
