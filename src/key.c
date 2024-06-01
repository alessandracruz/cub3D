/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:01:10 by matlopes          #+#    #+#             */
/*   Updated: 2024/06/01 10:38:51 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == KEY_ESC)
		data->key.close = 1;
	if (key == KEY_LEFT)
		data->key.left = 1;
	if (key == KEY_RIGHT)
		data->key.right = 1;
	if (key == KEY_W)
		data->key.w = 1;
	if (key == KEY_A)
		data->key.a = 1;
	if (key == KEY_D)
		data->key.d = 1;
	if (key == KEY_S)
		data->key.s = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_ESC)
		data->key.close = 0;
	if (key == KEY_LEFT)
		data->key.left = 0;
	if (key == KEY_RIGHT)
		data->key.right = 0;
	if (key == KEY_W)
		data->key.w = 0;
	if (key == KEY_A)
		data->key.a = 0;
	if (key == KEY_D)
		data->key.d = 0;
	if (key == KEY_S)
		data->key.s = 0;
	return (0);
}

int	key(t_data *data)
{
	int	check;

	check = 0;
	if (data->key.close)
		close_hook(data);
	if (data->key.left)
		check = rotate(data, 1);
	if (data->key.right)
		check = rotate(data, -1);
	if (data->key.w)
		check = move_ver(data, 1);
	if (data->key.a)
		check = move_hor(data, -1);
	if (data->key.d)
		check = move_hor(data, 1);
	if (data->key.s)
		check = move_ver(data, -1);
	if (check)
		load_map(data);
	return (0);
}
