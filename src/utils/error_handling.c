/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:28:12 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/19 23:44:38 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Trata erros registrando e realizando a limpeza
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
	clean_up(data);
	exit(error_code);
}

// Define os detalhes do erro na estrutura de erro fornecida
void	set_error(t_error *error, char *message, int code)
{
	error->message = message;
	error->error_code = code;
}
