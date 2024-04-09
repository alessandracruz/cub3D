/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:11:45 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/09 15:55:00 by acastilh         ###   ########.fr       */
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
		if (is_map_line(line))
			// Supondo que esta função verifica se é uma linha do mapa
		{
			line_count++;
		}
		free(line);
	}
	close(fd);
	return (line_count);
}

void	free_map_grid(char ***grid, int line_count)
{
	int	j;

	j = 0;
	while (j < line_count && (*grid)[j] != NULL)
	{
		free((*grid)[j]);
		j++;
	}
	free(*grid);
	*grid = NULL;
}

bool	fill_map_grid(int fd, char ***grid, int line_count)
{
	char	*line;
	int		i;

	i = 0;
	while ((line = get_next_line(fd)) != NULL && i < line_count)
	{
		(*grid)[i++] = line;
	}
	// Trata o caso de leitura de menos linhas do que o esperado
	if (i < line_count || (line = get_next_line(fd)) != NULL)
	{
		if (line != NULL)
			free(line);         // Se ainda existir linha após atingir o limite, libera a linha.
		free_map_grid(grid, i); // Libera as linhas já alocadas e o grid
		return (false);
	}
	return (true);
}

bool	process_map(t_data *data, const char *file_path)
{
	int	fd;

	data->map.line_count = count_map_lines(file_path);
	if (data->map.line_count <= 0)
		return (false);
	data->map.grid = (char **)malloc(sizeof(char *) * data->map.line_count);
	if (data->map.grid == NULL)
		return (false);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		free(data->map.grid);
		return (false);
	}
	if (!fill_map_grid(fd, &data->map.grid, data->map.line_count))
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
