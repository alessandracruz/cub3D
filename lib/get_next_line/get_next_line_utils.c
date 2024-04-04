/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:07:45 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/04 01:07:19 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

const char *ft_strchr(const char *s, int c)
{
    if (!s) return NULL;

    while (*s != '\0') {
        if (*s == (char)c) {
            return (s);
        }
        s++;
    }
    if (c == '\0') {
        return (s);
    }
    return (NULL);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;
	char	*str_iter;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
	{
		return (NULL);
	}
	str_iter = str;
	while (*s1 != '\0')
	{
		*str_iter++ = *s1++;
	}
	while (*s2 != '\0')
	{
		*str_iter++ = *s2++;
	}
	*str_iter = '\0';
	return (str);
}

char	*return_line(char *aux_str)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!aux_str[i])
		return (NULL);
	while (aux_str[i] && aux_str[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (aux_str[i] && aux_str[i] != '\n')
	{
		str[i] = aux_str[i];
		i++;
	}
	if (aux_str[i] == '\n')
	{
		str[i] = aux_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*new_aux_str(char *aux_str)
{
	size_t	i;
	size_t	a;
	char	*str;

	a = 0;
	while (aux_str[a] && aux_str[a] != '\n')
		a++;
	if (!aux_str[a])
	{
		free(aux_str);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(aux_str) - a + 1));
	if (!str)
		return (NULL);
	i = 0;
	a++;
	while (aux_str[a])
		str[i++] = aux_str[a++];
	str[i] = '\0';
	free(aux_str);
	return (str);
}
