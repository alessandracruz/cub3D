/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:01:10 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/21 11:20:47 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_ver(t_data *data, int type)
{
	double	mov_speed;

	mov_speed = 0.05;
	if (type == -1)
	{
		if (data->map.grid[(int)(data->lmap.pos_x - data->lmap.dir_x
				* mov_speed)][(int)data->lmap.pos_y] == '0')
			data->lmap.pos_x -= data->lmap.dir_x * mov_speed;
		if (data->map.grid[(int)(data->lmap.pos_x)][(int)
				(data->lmap.pos_y - data->lmap.dir_y * mov_speed)] == '0')
			data->lmap.pos_y -= data->lmap.dir_y * mov_speed;
	}
	else
	{
		if (data->map.grid[(int)(data->lmap.pos_x + data->lmap.dir_x
				* mov_speed)][(int)data->lmap.pos_y] == '0')
			data->lmap.pos_x += data->lmap.dir_x * mov_speed;
		if (data->map.grid[(int)(data->lmap.pos_x)][(int)
				(data->lmap.pos_y + data->lmap.dir_y * mov_speed)] == '0')
			data->lmap.pos_y += data->lmap.dir_y * mov_speed;
	}
	return (1);
}

int	move_hor(t_data *data, int type)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.015;
	old_dir_x = data->lmap.dir_x;
	old_plane_x = data->lmap.plane_x;
	data->lmap.dir_x = data->lmap.dir_x * cos(type * rot_speed)
		- data->lmap.dir_y * sin(type * rot_speed);
	data->lmap.dir_y = old_dir_x * sin(type * rot_speed)
		+ data->lmap.dir_y * cos(type * rot_speed);
	data->lmap.plane_x = data->lmap.plane_x * cos(type * rot_speed)
		- data->lmap.plane_y * sin(type * rot_speed);
	data->lmap.plane_y = old_plane_x * sin(type * rot_speed)
		+ data->lmap.plane_y * cos(type * rot_speed);
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
