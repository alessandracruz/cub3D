/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:34:05 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 08:32:22 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **array)
{
	int	i;

	if (array != NULL)
	{
		i = 0;
		while (array[i] != NULL)
			free(array[i++]);
		free(array);
	}
}
