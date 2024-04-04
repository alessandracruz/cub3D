/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:07:07 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/03 18:18:22 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(char *line, t_config *config)
{
	char	*trimmed_line;

	// Removemos espaços em branco do início e final da linha
	trimmed_line = ft_strtrim(line, " \t\n");
	if (!trimmed_line)
	{
		config->parse_error = ERROR_MEMORY;
		return ;
	}
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line,
			"SO ", 3) == 0 || ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0)
	{
		if (!parse_texture_line(trimmed_line, &config->textures))
		{
			config->parse_error = ERROR_TEXTURE;
		}
	}
	else if (ft_strncmp(trimmed_line, "F ", 2) == 0 || ft_strncmp(trimmed_line,
			"C ", 2) == 0)
	{
		if (!parse_color_line(trimmed_line, &config->colors))
		{
			config->parse_error = ERROR_COLOR;
		}
	}
	else if (!parse_map_line(trimmed_line, &config->map))
	{
		config->parse_error = ERROR_MAP;
	}
	free(trimmed_line);
}

bool	parse_texture_line(char *line, t_texture *textures)
{
	const char	*path_start;

	path_start = ft_strchr(line, ' ');
	if (!path_start)
		return (false);
	path_start = ft_strtrim(path_start, " \t");
		// Remover espaços antes do caminho.
	if (!path_start)
		return (false);
	if (ft_strncmp(line, "NO ", 3) == 0)
		ft_strlcpy(textures->north, path_start, TEX_PATH_LEN);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		ft_strlcpy(textures->south, path_start, TEX_PATH_LEN);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		ft_strlcpy(textures->west, path_start, TEX_PATH_LEN);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		ft_strlcpy(textures->east, path_start, TEX_PATH_LEN);
	else
		return (false);
	return (true);
}

bool	parse_color_line(char *line, t_color *colors)
{
	char	**rgb;

	int r, g, b;
	char *trimmed = ft_strtrim(line + 1, " \t");
		// Pular o identificador e trimar.
	if (!trimmed)
		return (false);
	rgb = ft_split(trimmed, ',');
	free(trimmed); // Liberar memória de trimmed após uso.
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{                      
		// Certificar-se de que existem exatamente três componentes.
		ft_free_split(rgb);
			// Supondo que essa função libera todos os elementos de rgb.
		return (false);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	colors->floor = (line[0] == 'F') ? (r << 16 | g << 8 | b) : colors->floor;
	colors->ceiling = (line[0] == 'C') ? (r << 16 | g << 8 | b) : colors->ceiling;
	return (true);
}

bool parse_map_line(char *line, t_map *map) {
    char **new_grid;
    int i = 0;

    // Alocar espaço para o novo grid, incluindo a nova linha e um espaço para NULL
    new_grid = (char **)malloc(sizeof(char *) * (map->height + 2));
    if (!new_grid) {
        return (false); // Falha na alocação de memória
    }

    // Copiar as linhas existentes para o novo grid
    while (i < map->height) {
        new_grid[i] = map->grid[i];
        i++;
    }

    // Adicionar a nova linha ao grid
    new_grid[i] = ft_strdup(line);
    if (!new_grid[i]) {
        // Falha ao duplicar a linha, limpar a memória alocada
        i--; // Decrementar i para começar a liberar a partir do último item válido
        while (i >= 0) {
            free(new_grid[i]);
            i--;
        }
        free(new_grid);
        return (false);
    }

    // Marcar o fim do novo grid
    new_grid[map->height + 1] = NULL;

    // Liberar o grid antigo se ele existir
    if (map->grid != NULL) {
        free(map->grid);
    }

    // Atualizar o grid do mapa e incrementar a altura
    map->grid = new_grid;
    map->height++;

    // Atualizar a largura do mapa se a nova linha for mais larga que as anteriores
    size_t new_line_length = ft_strlen(line);
    if (new_line_length > (size_t)map->width) {
        map->width = (int)new_line_length;
    } else {
        // Se a nova linha não é mais larga, mantém a largura atual
        map->width = map->width;
    }

    return (true); // Sucesso
}
