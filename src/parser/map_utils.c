/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:11:45 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/08 21:03:06 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Função para contar as linhas do mapa.
int	count_map_lines(const char *file_path)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening file: %s\n", file_path);
		return (-1);
	}
	line_count = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line)) // Supondo que esta função verifica se é uma linha do mapa
		{
			line_count++;
		}
		free(line);
	}
	close(fd);
	return (line_count);
}


// Função revisada para processar o mapa.
bool	process_map(t_data *data, const char *file_path)
{
	int		fd;
	char	*line;

	data->map.line_count = count_map_lines(file_path);
	if (data->map.line_count <= 0)
	{
		return (false); // Falha ao contar linhas ou mapa vazio.
	}
	data->map.grid = (char **)malloc(sizeof(char *) * data->map.line_count);
	if (data->map.grid == NULL)
	{
		return (false); // Falha ao alocar o array de grid.
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		free(data->map.grid);
		return (false);
	}
	for (int i = 0; (line = get_next_line(fd)) != NULL; ++i)
	{
		data->map.grid[i] = line;
			// Aqui você guarda diretamente a linha no grid.
	}
	close(fd);
	return (true);
}
