/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:28:53 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/19 23:41:34 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_config(const char *filename, t_error *error)
{
	FILE	*file;
	bool	result;

	file = fopen(filename, "r");
	if (!file)
	{
		set_error(error, "Failed to open file", ERROR_MEMORY);
		return (false);
	}
	result = process_file(file, error);
	fclose(file);
	return (result);
}

bool	process_file(FILE *file, t_error *error)
{
	char	buffer[1024];
	int		fd;
	int		bytes_read;

	fd = fileno(file);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!process_buffer(buffer, error))
		{
			return (false);
		}
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	}
	(void)error;
	return (true);
}

bool	process_buffer(const char *buffer, t_error *error)
{
	const char	*ptr = buffer;
	bool		player_found;

	player_found = false;
	while (*ptr)
	{
		if (is_path_or_config_line(ptr))
		{
			ptr += skip_to_next_line(ptr); // Avança para a próxima linha
			continue ;
		}
		if (!is_valid_character(*ptr))
		{
			ft_printf("Invalid character: %c\n", *ptr); // Para debugar
			set_error(error, "Invalid character found", ERROR_INVALID_CHAR);
			return (false);
		}
		if (ft_strchr("NSEW", *ptr))
		{
			if (player_found)
			{
				set_error(error, "Multiple players found",
					ERROR_MULTIPLE_PLAYERS);
				return (false);
			}
			player_found = true;
		}
		ptr++;
	}
	return (true);
}

// Verifica se a linha atual é uma linha de configuração ou caminho de arquivo
bool	is_path_or_config_line(const char *line)
{
	return (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0
		|| strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0
		|| strncmp(line, "C ", 2) == 0 || strncmp(line, "F ", 2) == 0);
}

// Retorna o número de caracteres a avançar para pular para a próxima linha
int	skip_to_next_line(const char *line)
{
	const char	*next_line = strchr(line, '\n');

	if (next_line != NULL)
	{
		return (next_line - line + 1);
			// Inclui o caractere de nova linha para mover para o início da próxima linha
	}
	return (0); // Se não encontrar uma nova linha, retorna 0
}

bool	is_valid_character(char c)
{
	return (ft_strchr(" 01NSEWO\n", c) != NULL);
}
