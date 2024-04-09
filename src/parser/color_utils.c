/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:52:12 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/08 19:10:31 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	process_color_line(char *line, t_data *data)
{
	int	color_hex;

	const char *color_str = ft_strchr(line, ' ') + 1;
		// Pula o identificador (F ou C) e o espaço.
	color_hex = convert_rgb_to_hex(color_str);
	if (color_hex == -1)
	{
		return (false); // Falha ao converter a string RGB para hex, possivelmente devido a um formato inválido.
	}
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		data->map.floor = color_hex; // Define a cor do chão.
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		data->map.ceiling = color_hex; // Define a cor do teto.
	}
	else
	{
		return (false);
			// A linha não corresponde a um identificador de cor conhecido.
	}
	return (true); // Processamento bem-sucedido.
}

int	convert_rgb_to_hex(const char *rgb)
{
	int r, g, b;
	// Assume que os valores RGB estão separados por vírgulas.
	r = ft_atoi(rgb);
	while (*rgb != ',' && *rgb != '\0')
		rgb++;
	rgb++; // Pula a vírgula
	g = ft_atoi(rgb);
	while (*rgb != ',' && *rgb != '\0')
		rgb++;
	rgb++; // Pula a vírgula
	b = ft_atoi(rgb);
	// Converte os valores RGB para um valor hexadecimal.
	return ((r << 16) | (g << 8) | b);
}
