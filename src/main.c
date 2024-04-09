/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:51:11 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/09 00:12:27 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	windows_builder(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, data->name);
	if (!data->win)
	{
		ft_printf("Failed to create window.\n");
		clean_up(data); // Libera recursos em caso de falha.
		handle_error(ERR_MLX_INIT_FAILED, data);       
			// Considerar tratamento de erro alternativo se não quiser sair imediatamente.
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		ft_printf("Failed to create image.\n");
		clean_up(data);
		handle_error(ERR_MLX_INIT_FAILED, data);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	clean_up(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->map.grid)
	{
		for (int i = 0; i < data->map.line_count; i++)
		{
			free(data->map.grid[i]);
		}
		free(data->map.grid);
	}
	// Adicionar aqui a liberação de qualquer outra memória alocada
}

int	close_hook(t_data *data)
{
	clean_up(data);
	exit(0); // Termina o programa.
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Usage: ./cub3D <path_to_map.cub>\n");
		return (1);
	}
	ft_bzero(&data, sizeof(t_data)); // Assume que ft_bzero zera a memória.
	data.map.grid = NULL;
	data.map.line_count = 0;
	data.mlx = mlx_init(); // Mova a inicialização do mlx para cá
	if (!data.mlx)
	{
		ft_printf("Failed to initialize MLX.\n");
		return (1); // Falha ao inicializar a MiniLibX.
	}
	if (!parse_config_file(argv[1], &data))
	{
		ft_printf("Failed to parse the map file.\n");
		clean_up(&data);
			// Chama clean_up para liberar recursos alocados até agora.
		return (1);
	}
	windows_builder(&data); // Inicializa a janela gráfica
	// Registrar a função de callback para o evento de fechamento da janela.
	mlx_hook(data.win, 17, 0L, close_hook, &data);
	mlx_loop(data.mlx); // Inicia o loop de eventos da MiniLibX
	return (0);
}
