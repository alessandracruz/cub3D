/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:07:07 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/28 00:00:30 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(char *line, t_config *config)
{
	line = get_next_line_trim(line);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!parse_texture_line(line, &config->textures))
		{
			config->parse_error = ERROR_TEXTURE;
			ft_printf("Error: Failed to parse texture line: %s\n", line);
		}
	}
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		if (!parse_color_line(line, &config->colors))
		{
			config->parse_error = ERROR_COLOR;
			ft_printf("Error: Failed to parse color line: %s\n", line);
		}
	}
	else
	{
		if (!parse_map_line(line, &config->map))
		{
			config->parse_error = ERROR_MAP;
			ft_printf("Error: Failed to parse map line: %s\n", line);
		}
	}
}

bool	parse_texture_line(char *line, t_texture *textures)
{
	const char *path_start = ft_strchr(line, ' '); // Encontra o primeiro espaço
	if (!path_start)
		return (false); // Retorna falso se não encontrar um espaço
	path_start++;       // Avança para começar do caminho, depois do espaço
	// Checa o identificador e copia o caminho para a estrutura apropriada
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		ft_strlcpy(textures->north, path_start, TEX_PATH_LEN);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		ft_strlcpy(textures->south, path_start, TEX_PATH_LEN);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		ft_strlcpy(textures->west, path_start, TEX_PATH_LEN);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		ft_strlcpy(textures->east, path_start, TEX_PATH_LEN);
	}
	else
	{
		return (false); // Retorna falso se o identificador não corresponder
	}
	return (true); // Retorna verdadeiro se a linha for analisada com sucesso
}

bool	parse_color_line(char *line, t_color *colors)
{
	char	**rgb;
	int		color;

	int r, g, b;
	char identifier = line[0]; // 'F' ou 'C'
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_free_split(rgb);
		return (false);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	// Verifica se os valores RGB são válidos
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		return (false); // Retorna falso se qualquer valor RGB for inválido
	}
	// Calcula o valor hexadecimal da cor
	color = (r << 16) | (g << 8) | b;
	// Armazena o valor hexadecimal na estrutura apropriada
	if (identifier == 'F')
	{
		colors->floor = color;
	}
	else if (identifier == 'C')
	{
		colors->ceiling = color;
	}
	else
	{
		return (false); // Retorna falso se o identificador não for 'F' nem 'C'
	}
	return (true); // Retorna verdadeiro se a linha for analisada com sucesso
}

bool	parse_map_line(char *line, t_map *map)
{
	char	**new_grid;
	int		line_length;

	int new_height = map->height + 1;
    new_grid = (char **)malloc(sizeof(char *) * (new_height + 1));
	if (!new_grid)
	{
		return (false); // Retorna falso se falhar a alocação de memória
	}
	// Copia as linhas existentes para o novo array
	for (int i = 0; i < map->height; i++) // mudar para while 
	{
		new_grid[i] = map->grid[i];
	}
	// Tenta duplicar a nova linha para o novo array
	new_grid[map->height] = ft_strdup(line);
	if (!new_grid[map->height])
	{ 
		while (--i >= 0)
		{
			free(new_grid[i]);
		}
		free(new_grid);
		return (false);
	}
	// Define o novo final do array
	new_grid[new_height] = NULL;
	// Libera o antigo array de linhas, se não for nulo
	if (map->grid != NULL)
	{
		free(map->grid);
	}
	// Atualiza o array de linhas do mapa e sua altura
	map->grid = new_grid;
	map->height = new_height;
	// Atualiza a largura do mapa se necessário
	line_length = ft_strlen(line);
	if (line_length > map->width)
	{
		map->width = line_length;
	}
	return (true); // Retorna verdadeiro se a linha for adicionada com sucesso
}
