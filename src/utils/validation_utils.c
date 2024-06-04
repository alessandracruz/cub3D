/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:36:52 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 10:10:25 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_config_line(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'O' || c == 'E'
		|| c == 'W');
}

bool	is_map_char(char c)
{
	return (ft_strchr("01NSEW ", c) != NULL);
}

bool	is_map_line(const char *line)
{
	if (!line || !*line)
		return (false);
	if (is_valid_config_line(line))
		return (false);
	while (*line)
	{
		if (!is_map_char(*line))
			return (false);
		line++;
	}
	return (true);
}

bool	is_valid_character(char c)
{
	return (ft_strchr(" 01NSEWO\n", c) != NULL);
}
