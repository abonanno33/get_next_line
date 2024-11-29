/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonanno <abonanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:57:45 by abonanno          #+#    #+#             */
/*   Updated: 2024/11/30 00:12:27 by abonanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	int		i;

	i = 0;
	ch = (char) c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == ch)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len_s;
	size_t	i;

	len_s = ft_strlen(s);
	ptr = (char *) malloc(sizeof(char) * (len_s + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	if (len_s + 1 > 0)
	{
		while ((i < len_s) && (s[i]))
		{
			ptr[i] = s[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

void	*ft_bzero(void *str, unsigned long int n)
{
	unsigned long int	i;
	unsigned char		*ptr;

	i = 0;
	ptr = (unsigned char *)str;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
	return (str);
}

void	*ft_realloc(unsigned char *ptr, size_t size)
{
	unsigned char	*new_ptr;
	size_t			i;

	if (size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	new_ptr = ft_bzero(new_ptr, size);
	if (ptr == NULL)
		return (new_ptr);
	i = 0;
	while (i < size && ptr[i])
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}
