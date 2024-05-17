/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:51:11 by acastilh          #+#    #+#             */
/*   Updated: 2024/05/17 11:03:00 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	windows_builder(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->win)
	{
		ft_printf("Failed to create window.\n");
		clean_up(data);
		exit(EXIT_FAILURE);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		ft_printf("Failed to create image.\n");
		clean_up(data);
		exit(EXIT_FAILURE);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	clean_up(t_data *data)
{
	int	i;

	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->map.grid)
	{
		i = 0;
		while (data->map.grid[i])
			free(data->map.grid[i++]);
		free(data->map.grid);
	}
}

int	close_hook(t_data *data)
{
	clean_up(data);
	exit(0);
}

int move_ver(t_data *data, int type)
{
	if (type == -1)
	{
		data->lmap.posX -= data->lmap.dirX * 0.2;
		data->lmap.posY -= data->lmap.dirY * 0.2;
	}
	else
	{
		data->lmap.posX += data->lmap.dirX * 0.2;
		data->lmap.posY += data->lmap.dirY * 0.2;
	}
	return (1);
}

int move_hor(t_data *data, int type)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = data->lmap.dirX;
	oldPlaneX = data->lmap.planeX;
	data->lmap.dirX = data->lmap.dirX * cos(type * 0.1) - data->lmap.dirY * sin(type * 0.1);
	data->lmap.dirY = oldDirX * sin(type * 0.1) + data->lmap.dirY * cos(type * 0.1);
	data->lmap.planeX = data->lmap.planeX * cos(type * 0.1) - data->lmap.planeY * sin(type * 0.1);
	data->lmap.planeY = oldPlaneX * sin(type * 0.1) + data->lmap.planeY * cos(type * 0.1);
	return (1);
}

int	key(int key, t_data *data)
{
	int check = 0;

	ft_printf("KEY=%d\n", key);
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

int	main(int argc, char **argv)
{
	t_data	data;
	t_error	err;

	if (argc != 2)
	{
		ft_printf("Usage: ./cub3D <path_to_map.cub>\n");
		return (EXIT_FAILURE);
	}
	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		ft_printf("Failed to initialize MLX.\n");
		return (EXIT_FAILURE);
	}
	if (!parse_config_file(argv[1], &data, &err) /* || !parse_config(argv[1], &err) */)
	{
		fprintf(stderr, "Erro: %s\n", err.message);
		return (EXIT_FAILURE);
	}
	windows_builder(&data);
	init_lmap(&data, &data.lmap);
	load_map(&data);
	mlx_hook(data.win, 2, 1L << 0, key, &data);
	mlx_hook(data.win, 17, 0L, close_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
