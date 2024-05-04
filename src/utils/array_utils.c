/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:59:10 by matlopes          #+#    #+#             */
/*   Updated: 2024/05/04 11:21:39 by matlopes         ###   ########.fr       */
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

char **ft_arraydup(char **array)
{
	int index;
	char **new_array;

	new_array = malloc((ft_arraylen(array) + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	index = -1;
	while (array && array[++index])
		new_array[index] = ft_strdup(array[index]);
	new_array[index] = NULL;
	return (new_array);
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
	new_array[index] = ft_strdup(str);
	new_array[index + 1] = NULL;
	if (array)
		free(array);
	return (new_array);
}

char	**fill_array_spaces(char **array)
{
	int		index;
	int 	length;
	char	**new_array;

	length = -1;
	index = -1;
	while (array[++index])
	{
		if ((int)ft_strlen(array[index]) > length)
		{
			if (array[index][ft_strlen(array[index]) - 1] == '\n')
				length = ft_strlen(array[index]) - 1;
			else
				length = ft_strlen(array[index]);
		}
	}
	new_array = malloc((ft_arraylen(array) + 1) * sizeof(char **));
	if (!new_array)
		return (NULL);
	index = -1;
	while (array[++index])
		new_array[index] = ft_strldup(array[index], length);
	new_array[index] = NULL;
	free(array);
	return (new_array);
}