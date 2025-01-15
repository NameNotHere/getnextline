/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otanovic <otanovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:52:02 by otanovic          #+#    #+#             */
/*   Updated: 2025/01/15 15:03:01 by otanovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <get_next_line.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_len(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*free_and_return_null(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		size;
	char	*dup;

	size = 0;
	dup = NULL;
	if (!str)
		return (NULL);
	while (str[size] != '\0')
		size++;
	dup = malloc(sizeof(char) * (size + 1));
	if (dup == NULL)
		return (NULL);
	size = 0;
	while (str[size] != '\0')
	{
		dup[size] = str[size];
		size++;
	}
	dup[size] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	new = (char *) malloc(ft_len(s1) + ft_len(s2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char	*ft_strchr(const char *s, int c, int MAX)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0' && i < MAX)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

int	loop(char *remainder, char *line, t_buffer_info buffer)
{
	char	*temp;
	char	*newline_pos;

	buffer.bytes_read = read(buffer.fd, buffer.buffer, BUFFER_SIZE);
	if (buffer.bytes_read < 0)
		return (free_and_return_null(&remainder));
	buffer.buffer[buffer.bytes_read] = '\0';
	temp = ft_strjoin(remainder, buffer.buffer);
	free_and_return_null(&remainder);
	remainder = temp;
	newline_pos = ft_strchr(remainder, '\n', ft_len(remainder));
	if (buffer.newline_pos)
	{
		*newline_pos = '\0';
		line = ft_strdup(remainder);
		temp = ft_strdup(newline_pos + 1);
		free_and_return_null(&remainder);
		remainder = temp;
		temp = line;
		line = ft_strjoin(line, "\n");
		free_and_return_null(&temp);
		return (line);
	}
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	//static char	buffer[BUFFER_SIZE + 1];
	buffer buffer;
	//char		*newline_pos;
	char		*line;
	static char	*remainder;
	//char *temp;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	while (bytes_read > 0)
	{
		/*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_and_return_null(&remainder));
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		free_and_return_null(&remainder);
		remainder = temp;
		newline_pos = ft_strchr(remainder, '\n', ft_len(remainder));
		if (newline_pos) // put this into a function
		{
			*newline_pos = '\0';
			line = ft_strdup(remainder);
			temp = ft_strdup(newline_pos + 1);
			free_and_return_null(&remainder);
			remainder = temp;
			temp = line;
			line = ft_strjoin(line, "\n");
			free_and_return_null(&temp);
			return (line);
		}*/
		loop(remainder, line, buffer);
	}
	if (bytes_read == 0 && remainder && remainder[0] != '\0')
	{
		line = ft_strdup(remainder);
		free_and_return_null(&remainder);
		return (line);
	}
	free_and_return_null(&remainder);
	return (NULL);
}
