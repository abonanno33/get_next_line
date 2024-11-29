/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonanno <abonanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:57:45 by abonanno          #+#    #+#             */
/*   Updated: 2024/11/29 18:54:40 by abonanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*i_dest;
	unsigned char	*i_src;

	i_dest = (unsigned char *) dest;
	i_src = (unsigned char *) src;
	i = 0;
	while (i < n && i_src[i])
	{
		i_dest[i] = i_src[i];
		i++;
	}
	return (dest);
}
void *ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;
	if(ptr == NULL && size == 0)
		return NULL;
	if(ptr == NULL && size != 0){
		new_ptr = malloc(size);
		return ft_bzero(new_ptr, size);
	}
	if(ptr != NULL && size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	new_ptr = ft_bzero(new_ptr, size);
	if(new_ptr == 0)
		return NULL;
	if(ptr != NULL && size != 0)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
		return new_ptr;
	}
	return NULL;
}
