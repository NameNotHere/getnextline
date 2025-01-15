/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otanovic <otanovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:52:02 by otanovic          #+#    #+#             */
/*   Updated: 2025/01/15 17:43:56 by otanovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
//#include <sys/types.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_len(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s && s[i] != '\0')
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

char	*process_line(int fd, ssize_t *bytes_read)
{
	char			buffer[BUFFER_SIZE + 1];
	char			*newline_pos;
	char			*temp;
	static char		*remainder;
	char			*line;

	if (!remainder)
		remainder = ft_strdup("");

	while (*bytes_read > 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == 0)
			break ;
		buffer[*bytes_read] = '\0';

		newline_pos = ft_strchr(buffer, '\n', BUFFER_SIZE);
		if (newline_pos)
		{
			*newline_pos = '\0';
			remainder = ft_strdup(newline_pos + 1); // you need to free remainder and maybe no if
		}

		line = ft_strjoin(remainder, buffer);
		if (newline_pos)
		{
			line = ft_strjoin(line , "\n");
			break ;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	line = process_line(fd, &bytes_read);
	if (!line)
		return (NULL);
	return (line);
}
