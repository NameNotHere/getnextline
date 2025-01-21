/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otanovic <otanovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:52:02 by otanovic          #+#    #+#             */
/*   Updated: 2025/01/21 16:23:36 by otanovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
#endif

void	get_the_line(char	**remainder, ssize_t *bytes_read, int fd)
{
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];

	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read > 0)
	{
		buffer[*bytes_read] = '\0';
		temp = *remainder;
		if (!*remainder)
			*remainder = ft_strdup(buffer);
		else
			*remainder = ft_strjoin(*remainder, buffer, 0, 0);
		free_and_return_null(&temp);
	}
}

char	*process_remainder(int fd, ssize_t *bytes_read, char **remainder, \
	char	*newline_pos)
{
	char	*line;
	char	*temp;

	while (*bytes_read > 0 || (*remainder && (*remainder)[0] != '\0'))
	{
		get_the_line(remainder, bytes_read, fd);
		if (!*remainder)
			return (NULL);
		newline_pos = ft_strchr(*remainder, '\n');
		if (newline_pos)
		{
			*newline_pos = '\0';
			line = ft_strjoin(*remainder, "\n", 0, 0);			
			temp = *remainder;
			*remainder = ft_strdup(newline_pos + 1);
			free_and_return_null(&temp);
			return (line);
		}
		else if (*remainder && (*remainder)[0] != '\0' && *bytes_read == 0)
		{
			line = ft_strdup(*remainder);
			free_and_return_null(remainder);
			return (line);
		}
	}
	return (NULL);
}

char	*process_line(int fd, ssize_t *bytes_read)
{
	static char		*remainder;
	char			*line;

	line = process_remainder(fd, bytes_read, &remainder, NULL);
	if (line == NULL && remainder && remainder[0] != '\0')
	{
		line = ft_strdup(remainder);
		free_and_return_null(&remainder);
	}
	if (line == NULL)
		return (NULL);
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
