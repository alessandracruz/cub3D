/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:07:56 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/19 23:42:08 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_config_file(char *file_path, t_data *data, t_error *error)
{
	int		fd;
	char	*line;
	int		valid_lines;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		set_error(error, "Error opening file", ERROR_FILE_OPEN);
		return (false);
	}
	valid_lines = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (*line != '\0' && process_line(line, data, error, fd))
		{
			valid_lines++;
		}
		free(line);
	}
	close(fd);
	if (valid_lines == 0)
	{
		set_error(error, "Empty or invalid map", ERROR_EMPTY_MAP);
		return (false);
	}
	return (true);
}

bool	process_line(char *line, t_data *data, t_error *error, int fd)
{
	ft_printf("Processando linha\n");
	if (!line || *line == '\0')
		return (true); // Ignora linhas vazias ou NULL
	// Ignora espaços no início da linha
	while (*line == ' ' || *line == '\n')
		line++;
	if (*line == '\0')
		return (true); // Se só tinha espaço ou quebra de linha, continua
	ft_printf("A linha começa com: %c\n", *line); // Para debugar
	if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
	{
		return (process_texture_line(line, data, error));
	}
	else if (*line == 'F' || *line == 'C')
	{
		return (process_color_line(line, data, error));
	}
	else
	{
		// Trata como linha de mapa
		return (process_map_line(data, fd, error));
	}
}
