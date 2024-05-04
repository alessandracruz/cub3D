/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:37:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/05/03 13:04:41 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strldup(char *str, int size)
{
	int		index;
	char *new_str;

	if ((int)ft_strlen(str) > size)
		new_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	else
		new_str = malloc((size + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	index = 0;
	while (str[index] && str[index] != '\n' && index < size)
	{
		new_str[index] = str[index];
		index++;
	}
	while (index < size)
		new_str[index++] = ' ';
	new_str[index] = '\0';
	free(str);
	return (new_str);
}

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
