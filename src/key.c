/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:01:10 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/17 13:06:53 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_ver(t_data *data, int type)
{
	double	mov_speed;

	mov_speed = 0.2;
	if (type == -1)
	{
		data->lmap.pos_x -= data->lmap.dir_x * mov_speed;
		data->lmap.pos_y -= data->lmap.dir_y * mov_speed;
	}
	else
	{
		data->lmap.pos_x += data->lmap.dir_x * mov_speed;
		data->lmap.pos_y += data->lmap.dir_y * mov_speed;
	}
	return (1);
}

int	move_hor(t_data *data, int type)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.1;
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

int	key(int key, t_data *data)
{
	int	check;

	check = 0;
	if (key == KEY_ESC)
		close_hook(data);
	if (key == KEY_W)
		check = move_ver(data, 1);
	if (key == KEY_A)
		check = move_hor(data, 1);
	if (key == KEY_D)
		check = move_hor(data, -1);
	if (key == KEY_S)
		check = move_ver(data, -1);
	if (check)
		load_map(data);
	return (0);
}
