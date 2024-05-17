/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:37:27 by acastilh          #+#    #+#             */
/*   Updated: 2024/05/17 13:12:49 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strldup(char *str, int size)
{
	int		index;
	char	*new_str;

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

char	*trim_spaces(char *str)
{
	char	*end;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (!*str)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = 0;
	return (str);
}
