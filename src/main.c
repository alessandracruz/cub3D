/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:51:11 by acastilh          #+#    #+#             */
/*   Updated: 2024/05/04 10:22:05 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	windows_builder(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, data->name);
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
	mlx_hook(data.win, 17, 0L, close_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
