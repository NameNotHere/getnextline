/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otanovic <otanovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:52:02 by otanovic          #+#    #+#             */
/*   Updated: 2025/01/18 14:05:47 by otanovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
#endif

char	*process_remainder(int fd, ssize_t *bytes_read, char **remainder)
{
	char	*newline_pos;
	char	*line;
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];

	while (*bytes_read > 0 || *remainder)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[*bytes_read] = '\0';
		temp = *remainder;
		*remainder = ft_strjoin(*remainder, buffer);
		free_and_return_null(&temp);
		newline_pos = ft_strchr(*remainder, '\n');
		if (newline_pos)
		{
			*newline_pos = '\0';
			temp = *remainder;
			if (newline_pos && newline_pos[1] != '\0')
				*remainder = ft_strdup(newline_pos + 1);
			line = ft_strjoin(temp, "\n");
			free_and_return_null(&temp);
			return (line);
		}
	}
	return (NULL);
}

char	*process_line(int fd, ssize_t *bytes_read)
{
	static char		*remainder;
	char			*line;

	if (!remainder)
		remainder = ft_strdup("");
	line = process_remainder(fd, bytes_read, &remainder);
	if (!line && remainder && remainder[0] != '\0')
	{
		line = ft_strdup(remainder);
		free_and_return_null(&remainder);
		return (line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t			bytes_read;
	char			*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	line = process_line(fd, &bytes_read);
	if (!line)
		return (NULL);
	return (line);
}
