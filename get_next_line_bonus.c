/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:45:06 by aldinc            #+#    #+#             */
/*   Updated: 2025/10/14 15:03:08 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Bu fonksiyon, zorunlu kısımdaki ile neredeyse aynı, sadece storage'a
// referans ile erişiyor.
static char	*ft_process_storage(char **storage)
{
	char	*line;
	char	*new_storage;
	char	*newline_ptr;
	int		len;

	newline_ptr = ft_strchr(*storage, '\n');
	if (newline_ptr)
	{
		len = (newline_ptr - *storage) + 1;
		line = (char *)malloc(sizeof(char) * (len + 1));
		if (!line)
			return (NULL);
		for (int i = 0; i < len; i++)
			line[i] = (*storage)[i];
		line[len] = '\0';
		
		new_storage = (char *)malloc(sizeof(char) * (ft_strlen(*storage) - len + 1));
		if (!new_storage)
		{
			free(line);
			return (NULL);
		}
		for (int i = 0, j = len; (*storage)[j]; i++, j++)
			new_storage[i] = (*storage)[j];
		new_storage[ft_strlen(*storage) - len] = '\0';
	}
	else
	{
		line = *storage;
		*storage = NULL;
		return (line);
	}
	free(*storage);
	*storage = new_storage;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage[FOPEN_MAX]; // <<<--- EN ÖNEMLİ DEĞİŞİKLİK
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(storage[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			if (storage[fd])
			    free(storage[fd]);
			storage[fd] = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		storage[fd] = ft_strjoin(storage[fd], buffer);
		if (!storage[fd])
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	if (!storage[fd] || *(storage[fd]) == '\0')
	{
		if (storage[fd])
		    free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	return (ft_process_storage(&storage[fd]));
}
