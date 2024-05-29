/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:01:10 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/29 12:56:48 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_ver(t_data *data, int type)
{
	if (type == -1)
	{
		if (data->map.grid[(int)(data->lmap.pos[X] - data->lmap.dir[X]
				* MOV_SPEED)][(int)data->lmap.pos[Y]] == '0')
			data->lmap.pos[X] -= data->lmap.dir[X] * MOV_SPEED;
		if (data->map.grid[(int)(data->lmap.pos[X])][(int)
				(data->lmap.pos[Y] - data->lmap.dir[Y] * MOV_SPEED)] == '0')
			data->lmap.pos[Y] -= data->lmap.dir[Y] * MOV_SPEED;
	}
	else
	{
		if (data->map.grid[(int)(data->lmap.pos[X] + data->lmap.dir[X]
				* MOV_SPEED)][(int)data->lmap.pos[Y]] == '0')
			data->lmap.pos[X] += data->lmap.dir[X] * MOV_SPEED;
		if (data->map.grid[(int)(data->lmap.pos[X])][(int)
				(data->lmap.pos[Y] + data->lmap.dir[Y] * MOV_SPEED)] == '0')
			data->lmap.pos[Y] += data->lmap.dir[Y] * MOV_SPEED;
	}
	return (1);
}

int	move_hor(t_data *data, int type)
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

int	key_press(int key, t_data *data)
{
	if (key == KEY_ESC)
		data->key.close = 1;
	if (key == KEY_W)
		data->key.up = 1;
	if (key == KEY_A)
		data->key.left = 1;
	if (key == KEY_D)
		data->key.right = 1;
	if (key == KEY_S)
		data->key.down = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_ESC)
		data->key.close = 0;
	if (key == KEY_W)
		data->key.up = 0;
	if (key == KEY_A)
		data->key.left = 0;
	if (key == KEY_D)
		data->key.right = 0;
	if (key == KEY_S)
		data->key.down = 0;
	return (0);
}

int	key(t_data *data)
{
	int	check;

	check = 0;
	if (data->key.close)
		close_hook(data);
	if (data->key.up)
		check = move_ver(data, 1);
	if (data->key.left)
		check = move_hor(data, 1);
	if (data->key.right)
		check = move_hor(data, -1);
	if (data->key.down)
		check = move_ver(data, -1);
	if (check)
		load_map(data);
	return (0);
}
