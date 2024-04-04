/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:35:44 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/03 18:04:50 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int read_map_config(char *file_path, t_config *config) {
    int fd;
    char *line;

    fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        ft_printf("Error: Failed to open file %s\n", file_path);
        return (-1);
    }
    while ((line = get_next_line(fd))) {
        parse_line(line, config);
        free(line);
        if (config->parse_error != PARSE_OK) {
            print_parse_error(config->parse_error, line);
            close(fd);
            return (-1);
        }
    }
    close(fd);
    
    // Verifica o resultado do parse após terminar de ler todas as linhas
    if (config->parse_error == PARSE_OK) {
        ft_printf("Map and settings parsed successfully.\n");
        return 0;
    } else {
        print_parse_error(config->parse_error, line);
        return -1;
    }
}

void print_parse_error(t_parse_error error_code, char *line) {
    if (error_code == ERROR_TEXTURE) {
        ft_printf("Error: Failed to parse texture line: %s\n", line);
    } else if (error_code == ERROR_COLOR) {
        ft_printf("Error: Failed to parse color line: %s\n", line);
    } else if (error_code == ERROR_MAP) {
        ft_printf("Error: Failed to parse map line: %s\n", line);
    } else if (error_code == ERROR_MEMORY) {
        ft_printf("Error: Memory allocation failed.\n");
    } else {
        ft_printf("Error: Unknown parsing error.\n");
    }
}
