/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:44:01 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/08 21:55:16 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdarg.h>
#include <time.h>

void log_message(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Gerar o timestamp atual
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char formatted_time[100];
    strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", t);

    // Abrir o arquivo de log em modo append
    FILE *file = fopen("cub3D.log", "a");
    if (file != NULL) {
        // Escrever o timestamp no arquivo
        fprintf(file, "[%s] ", formatted_time);
        // Escrever a mensagem formatada no arquivo
        vfprintf(file, format, args);
        fprintf(file, "\n"); // Nova linha no final
        fclose(file);
    }

    va_end(args);
}

