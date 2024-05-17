/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:44:01 by acastilh          #+#    #+#             */
/*   Updated: 2024/05/17 13:17:13 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdarg.h>
#include <time.h>

void	log_message(const char *format, ...)
{
	struct tm	*t;
	time_t		now;
	va_list		args;
	FILE		*file;
	char		formatted_time[100];

	va_start(args, format);
	now = time(NULL);
	t = localtime(&now);
	strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", t);
	file = fopen("cub3D.log", "a");
	if (file != NULL)
	{
		fprintf(file, "[%s] ", formatted_time);
		vfprintf(file, format, args);
		fprintf(file, "\n");
		fclose(file);
	}
	va_end(args);
}
