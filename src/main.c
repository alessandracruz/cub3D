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

#include "cub3d.h"

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

int	is_cub(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (ft_strcmp((str + len - 4), ".cub"))
		return (1);
	return (0);
}

int	check_args(char *s[], int argc)
{
	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.cub>\n", s[0]);
		return (0);
	}
	if (!is_cub(s[1]))
	{
		ft_printf("Usage: %s <map_file.cub>\n", s[0]);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (!check_args(argv, argc))
		exit (1);
	ft_bzero(&config, sizeof(t_config));
	if (read_map_config(argv[1], &config) == -1)
	{
		return (1);
	}
	ft_printf("Map read successfully.\n");
	return (0);
}
