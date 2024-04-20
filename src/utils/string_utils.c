/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:37:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/19 23:46:25 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Remove espaços do início e do fim da string
char	*trim_spaces(char *str)
{
	char	*end;

	// Remover espaços iniciais
	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0) // Todos os espaços?
		return (str);
	// Remover espaços iniciais
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	//  Escrever novo nulo
	*(end + 1) = 0;
	return (str);
}
