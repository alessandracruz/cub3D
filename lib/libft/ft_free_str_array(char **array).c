/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array(char **array).c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:53:36 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/25 19:53:55 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_free_str_array(char **array)
{
    if (array != NULL)
    {
        int i = 0;
        while (array[i] != NULL)
        {
            free(array[i]);
            i++;
        }
        free(array);
    }
}
