/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:07:56 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/08 22:01:59 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Implementações dummy para teste.

void	start(t_data *data)
{
	data->name = "Cub3D";
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_printf("Failed to initialize MLX.\n");
		exit(1); // Ou outra forma de tratamento de erro
	}
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, data->name);
	if (!data->win)
	{
		ft_printf("Failed to create window.\n");
		exit(1); // Ou outra forma de tratamento de erro
	}
}

bool	parse_config_file(char *file_path, t_data *data)
{
	int		fd;
	char	*line;
	int		read_status;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening file: %s\n", file_path);
		return (false);
	}
	read_status = 1;
	while (read_status > 0)
	{
		line = get_next_line(fd);
		if (!line)
		{                    // Se get_next_line retornar NULL, significa EOF ou erro.
			read_status = 0; // Define read_status para 0 para sair do loop.
			continue ;
		}
		if ((line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
				|| line[0] == 'E') && !process_texture_line(line, data))
		{
			free(line);
			close(fd);
			return (false);
		}
		else if ((line[0] == 'F' || line[0] == 'C') && !process_color_line(line,
				data))
		{
			free(line);
			close(fd);
			return (false);
		}
		else if (!process_map(data, file_path))
		{
			free(line);
			close(fd);
			return (false);
		}
		free(line);
			// Libera a memória alocada por get_next_line após processar a linha.
	}
	close(fd);
	return (true);
		// Retorna true se todo o arquivo foi processado sem encontrar erros.
}
