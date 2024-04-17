/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:06:30 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/17 18:54:54 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*read_line(int fd, char *str);
char	*take_line(char *str);
void	*gnl_calloc(int count, int size);
char	*gnl_strchr(char *str, int c);
char	*gnl_strjoin(char *s1, char *s2);
size_t	gnl_strlen(char *str);
char	*take_line(char *str);
char	*clean_buffer(char *buffer);

#endif