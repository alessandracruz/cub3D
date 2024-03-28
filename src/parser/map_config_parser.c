/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:35:44 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/27 23:11:14 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map_config(char *file_path, t_config *config)
{
	int		fd;
	int		read_status;
	char	*line;

	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
	{
		ft_printf("Error: Failed to allocate memory for line buffer\n");
		return (-1);
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Failed to open file %s\n", file_path);
		free(line);
		return (-1);
	}
	while ((read_status = read(fd, line, BUFFER_SIZE)) > 0)
	{
		line[read_status] = '\0';
		parse_line(line, config);
	}
	if (read_status == -1)
	{
		ft_printf("Error: Failed to read from file %s\n", file_path);
		close(fd);
		free(line);
		return (-1);
	}
	close(fd);
	free(line);
	return (0);
}
