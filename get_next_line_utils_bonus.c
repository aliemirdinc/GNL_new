/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:45:31 by aldinc            #+#    #+#             */
/*   Updated: 2025/10/14 15:03:08 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Bir string'in uzunluğunu hesaplar.
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

// Bir string içinde belirli bir karakteri arar.
// Bulursa karakterin adresini, bulamazsa NULL döner.
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

// İki string'i birleştirip yeni bir string oluşturur.
// İlk string'i (s1) serbest bırakır, çünkü bu bizim 'storage' değişkenimiz olacak.
char	*ft_strjoin(char *s1, const char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (s1[++i])
		new_str[i] = s1[i];
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free(s1); // Eski storage'ı temizle
	return (new_str);
}
