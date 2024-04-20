/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:36:52 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/19 23:46:41 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Verifica se a linha é válida para textura ou cor
bool	is_valid_config_line(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

// Verifica se o caracter é válido para o mapa
bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'O' || c == 'E'
		|| c == 'W');
}

bool	is_map_char(char c)
{
	ft_printf("linha completa: %c:\n", c);
	return (ft_strchr("01NSEW ", c) != NULL);
}

bool	is_map_line(const char *line)
{
	if (!line || !*line)
		return (false);
	// Linhas de configuração de texturas ou cores não são linhas de mapa
	if (is_valid_config_line(line))
		return (false);
	// Verifica se todos os caracteres são válidos para uma linha de mapa
	while (*line)
	{
		if (!is_map_char(*line))
			return (false);
		line++;
	}
	return (true);
}
