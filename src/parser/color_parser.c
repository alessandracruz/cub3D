/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:52:12 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 08:03:21 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_rgb_to_hex(const char *rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb);
	while (*rgb != ',' && *rgb != '\0')
		rgb++;
	rgb++;
	g = ft_atoi(rgb);
	while (*rgb != ',' && *rgb != '\0')
		rgb++;
	rgb++;
	b = ft_atoi(rgb);
	return ((r << 16) | (g << 8) | b);
}

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
		data->map.floor = color_hex;
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->map.ceiling = color_hex;
	else
	{
		set_error(error, "Unknown color identifier", ERROR_UNKNOWN_IDENTIFIER);
		return (false);
	}
	return (true);
}
