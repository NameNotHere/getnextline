/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otanovic <otanovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:52:16 by otanovic          #+#    #+#             */
/*   Updated: 2025/01/20 14:12:17 by otanovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>

char	*process_remainder(int fd, ssize_t *bytes_read, char **remainder, \
		char *newline_pos);
char	*free_and_return_null(char **ptr);
int		ft_len(char *s);
char	*ft_strjoin(char const *s1, char const *s2, int i, int j);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *str);
char	*process_line(int fd, ssize_t *bytes_read);
char	*get_next_line(int fd);

#endif