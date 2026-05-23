/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:03:57 by aldinc            #+#    #+#             */
/*   Updated: 2026/05/23 15:03:59 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_extracted_line(char *storage, char *nl)
{
	char	*line;
	size_t	i;
	size_t	len;

	if (!nl)
		return (ft_strjoin(NULL, storage));
	len = nl - storage + 1;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_extract_line(char **storage)
{
	char	*line;
	char	*remnant;
	char	*nl;

	nl = ft_strchr(*storage, '\n');
	line = get_extracted_line(*storage, nl);
	if (!line)
		return (ft_free_and_null(storage));
	if (!nl)
	{
		ft_free_and_null(storage);
		return (line);
	}
	remnant = ft_strjoin(NULL, nl + 1);
	ft_free_and_null(storage);
	if (!remnant)
	{
		free(line);
		return (NULL);
	}
	*storage = remnant;
	return (line);
}

static char	*read_till_newline(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free_and_null(&storage));
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (ft_free_and_null(&storage));
		}
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			break ;
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	storage[fd] = read_till_newline(fd, storage[fd]);
	if (!storage[fd] || !*storage[fd])
		return (ft_free_and_null(&storage[fd]));
	return (ft_extract_line(&storage[fd]));
}
