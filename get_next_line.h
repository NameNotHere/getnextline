/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otanovic <otanovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:52:16 by otanovic          #+#    #+#             */
/*   Updated: 2025/01/15 14:58:24 by otanovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct t_buffer_info
{
	ssize_t	bytes_read;
	char	*newline_pos;
	char	*buffer;
	int		fd;
}	t_buffer_info;

int		len(const char *s);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *str);
