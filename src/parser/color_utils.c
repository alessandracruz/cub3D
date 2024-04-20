/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:52:12 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/18 17:15:31 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	process_color_line(char *line, t_data *data, t_error *error)
{
	int			color_hex;
	const char	*color_str = trim_spaces(line + 1);

	if (!color_str)
	{
		set_error(error, "Invalid color format", ERROR_INVALID_FORMAT);
		return (false);
	}
	color_hex = convert_rgb_to_hex(color_str);
	if (color_hex == -1)
	{
		set_error(error, "RGB to Hex conversion failed",
			ERROR_CONVERSION_FAILED);
		return (false);
	}
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		data->map.floor = color_hex;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		data->map.ceiling = color_hex;
	}
	else
	{
		set_error(error, "Unknown color identifier", ERROR_UNKNOWN_IDENTIFIER);
		return (false);
	}
	return (true);
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
