/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:44:27 by aldinc            #+#    #+#             */
/*   Updated: 2025/10/14 13:44:42 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // malloc, free için
# include <unistd.h> // read için

// BUFFER_SIZE tanımlı değilse, varsayılan bir değer atayalım.
// Bu, -D BUFFER_SIZE bayrağı olmadan da derlemeyi mümkün kılar[cite: 103].
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

// Yardımcı fonksiyonların prototipleri
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, const char *s2);

#endif
