/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:28:12 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/08 21:30:53 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Em error_handling.c

#include "cub3d.h"

void	handle_error(int error_code, t_data *data)
{
	if (error_code == ERR_MLX_INIT_FAILED)
	{
		ft_printf("Failed to initialize MLX.\n");
	}
	else if (error_code == ERR_WIN_CREATION_FAILED)
	{
		ft_printf("Failed to create window.\n");
	}
	else if (error_code == ERR_IMG_CREATION_FAILED)
	{
		ft_printf("Failed to create image.\n");
	}
	else if (error_code == ERR_MAP_PARSING_FAILED)
	{
		ft_printf("Failed to parse the map file.\n");
	}
	// Adicione mais condições conforme necessário
	clean_up(data);
	exit(error_code);
}
