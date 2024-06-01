/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:53:36 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 08:33:42 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_str_array(char **array)
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
