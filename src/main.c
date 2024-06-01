/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:51:11 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 09:59:43 by matlopes         ###   ########.fr       */
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
	data->img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.ptr)
	{
		ft_printf("Failed to create image.\n");
		clean_up(data);
		exit(EXIT_FAILURE);
	}
	data->img.addr = (int *)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.size_line, &data->img.endian);
}

void	clean_up(t_data *data)
{
	int	i;

	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
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

void	init_game(t_data *data)
{
	data->key.close = 0;
	data->key.up = 0;
	data->key.left = 0;
	data->key.right = 0;
	data->key.down = 0;
	windows_builder(data);
	load_map(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0, close_hook, data);
	mlx_loop_hook(data->mlx, key, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_error	err;

	if (argc != 2 || ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 5))
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
	if (!parse_config(argv[1], &data, &err))
	{
		fprintf(stderr, "Erro: %s\n", err.message);
		return (EXIT_FAILURE);
	}
	init_game(&data);
	return (0);
}
