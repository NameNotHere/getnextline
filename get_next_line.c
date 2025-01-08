#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4
#endif

int	len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char *free_and_return_null(char **ptr)
{
    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
	else if (ptr != NULL)
		free(ptr);

    return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		size;
	char	*dup;

	size = 0;
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	new = (char *) malloc(len(s1) + len(s2) + 1);
	if (!new || !s1 || !s2)
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

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char *get_next_line(int fd)
{
    static char *remainder;
    char buffer[BUFFER_SIZE];
    char *line;
    char *newline_pos;
    ssize_t bytes_read;
	char *temp;

	newline_pos = NULL;
	line = NULL;
	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
    while ((newline_pos = ft_strchr(remainder, '\n')) == NULL)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
            return (free_and_return_null(&remainder));
        if (bytes_read == 0)
            break;
		buffer[bytes_read] = '\0';
		temp = ft_strdup(remainder);
        remainder = ft_strjoin(remainder, buffer);
		if (temp != NULL)
			free(temp);
		if (!remainder) 
			return (free_and_return_null(&remainder));
    }
	if (newline_pos)
	{
    	*newline_pos = '\0';
		line = ft_strdup(remainder);
		temp = ft_strjoin(line, "\n");
		if (!line || !temp)
		{
			free(line);
			return (free_and_return_null(&remainder));
		}
		free(line);
		line = temp;
		free_and_return_null(&temp);

		temp = remainder;
    	remainder = ft_strdup(newline_pos + 1);
		if (!remainder)
			free(temp);
	}
	else
	{
		line = ft_strdup(remainder);
		if (!line)
			return (free_and_return_null(&remainder));
	}
	return (line);
}

/*
int main()
{
	int fd = open("C:\\Users\\Orhan\\Desktop\\GetNextLine\\wewe.txt", 0);
	if (fd < 0)
	{
   		perror("Error opening file");
    	return 1;
	}

	char *i = get_next_line(fd);
	printf("%s", i);
	i = get_next_line(fd);
	printf("%s", i);
	i = get_next_line(fd); 
	printf("%s", i);

}*/