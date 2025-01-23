/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otanovic <otanovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:52:02 by otanovic          #+#    #+#             */
/*   Updated: 2025/01/23 16:02:32 by otanovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

void	get_the_line(char	**remainder, ssize_t *bytes_read, int fd)
{
	char		*temp;
	char		*buffer;

	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return ;
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read > 0)
	{
		buffer[*bytes_read] = '\0';
		if (!*remainder)
			*remainder = ft_strdup(buffer);
		else
		{
			temp = *remainder;
			*remainder = ft_strjoin(*remainder, buffer, 0, 0);
			free_and_return_null(&temp);
		}
		free_and_return_null(&buffer);
		return ;
	}
	free_and_return_null(&buffer);
}

char	*process_remainder(int fd, ssize_t *bytes_read, char **remainder, \
	char *newline_pos)
{
	char	*line;
	char	*temp;

	get_the_line(remainder, bytes_read, fd);
	while (*bytes_read >= 0 && (*remainder && (*remainder)[0] != '\0'))
	{
		newline_pos = ft_strchr(*remainder, '\n');
		if (newline_pos && *remainder)
		{
			*newline_pos = '\0';
			line = ft_strjoin(*remainder, "\n", 0, 0);
			temp = *remainder;
			*remainder = ft_strdup(newline_pos + 1);
			free(temp);
			return (line);
		}
		else if (*remainder && (*remainder)[0] != '\0' && *bytes_read == 0)
		{
			line = ft_strdup(*remainder);
			free_and_return_null(remainder);
			return (line);
		}
		get_the_line(remainder, bytes_read, fd);
	}
	return (free_and_return_null(remainder));
}

char	*process_line(int fd, ssize_t *bytes_read, char	**remainder)
{
	char			*line;

	if (!*remainder)
		*remainder = ft_strdup("");
	line = process_remainder(fd, bytes_read, remainder, NULL);
	if (line == NULL && *remainder && *remainder[0] != '\0')
	{
		line = ft_strdup(*remainder);
		free(remainder);
	}
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t			bytes_read;
	char			*line;
	static char		*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > _SC_SSIZE_MAX)
		return (free_and_return_null(&remainder));
	bytes_read = 1;
	line = process_line(fd, &bytes_read, &remainder);
	if (!line)
		return (free_and_return_null(&remainder));
	return (line);
}
