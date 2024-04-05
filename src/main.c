/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:51:11 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/04 19:16:18 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3d.h"

/*
int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (read_map_config(argv[1], &config) == -1)
	{
		ft_printf("Failed to read the map configuration.\n");
		return (1);
	}
	ft_printf("Map read successfully.\n");
	return (0);
}
*/

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	ft_bzero(&config, sizeof(t_config));
	if (read_map_config(argv[1], &config) == -1)
	{
		return (1);
	}
	ft_printf("Map read successfully.\n");
	return (0);
}
