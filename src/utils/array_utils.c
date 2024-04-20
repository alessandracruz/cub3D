/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:59:10 by matlopes          #+#    #+#             */
/*   Updated: 2024/04/20 15:59:40 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_arraylen(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return (index);
	while (array[index])
		index++;
	return (index);
}

char	**add_str_in_array(char **array, char *str)
{
	int		index;
	char	**new_array;

	new_array = malloc((ft_arraylen(array) + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	index = 0;
	while (array && array[index])
	{
		new_array[index] = array[index];
		index++;
	}
	new_array[index] = str;
	new_array[index + 1] = NULL;
	if (array)
		free(array);
	return (new_array);
}
