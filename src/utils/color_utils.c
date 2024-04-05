/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:23:59 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/04 18:30:57 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_colors_loaded(t_color *colors)
{
	return (colors->floor != -1 && colors->ceiling != -1);
}

bool	validate_color(int color)
{
	if (color < 0x000000 || color > 0xFFFFFF)
	{
		return (false);
	}
    ft_printf("Color validated successfully: %06X\n", color);
    return (true);
}
