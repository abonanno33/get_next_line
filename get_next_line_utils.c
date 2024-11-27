/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonanno <abonanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:57:45 by abonanno          #+#    #+#             */
/*   Updated: 2024/11/27 16:18:14 by abonanno         ###   ########.fr       */
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while ((i < size - 1) && (src[i]))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t	i;
    size_t	dst_len;

    dst_len = ft_strlen(dst);
    i = 0;
    if (size > dst_len)
    {
        while ((i < size - dst_len - 1) && (src[i]))
        {
            dst[dst_len + i] = src[i];
            i++;
        }
        dst[dst_len + i] = 0;
    }
    return (dst_len + ft_strlen(src));
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

    len_s = ft_strlen(s);
    ptr = (char *) malloc(sizeof(char) * (len_s + 1));
    if (ptr == NULL)
        return (NULL);
    ft_strlcpy(ptr, s, len_s + 1);
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

void	*ft_calloc(size_t nmemb, size_t size)
{
    void	*ptr;

    ptr = (void *) malloc(nmemb * size);
    if (ptr == NULL)
        return (NULL);
    ft_bzero(ptr, nmemb * size);
    return (ptr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t			i;
    unsigned char	*i_dest;
    unsigned char	*i_src;

    i_dest = (unsigned char *) dest;
    i_src = (unsigned char *) src;
    i = 0;
    while (i < n)
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
    if(ptr == NULL && size != 0)
        return malloc(size);
    if(ptr != NULL && size == 0)
    {
        free(ptr);
        return (NULL);
    }
    new_ptr = malloc(size);
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

int	app_get_next_line(char **str, char **save, ssize_t rd, int i)
{
    char	*chr_res;
    size_t	new_len;

    if (rd == -1)
        return (-1);
    if (rd < BUFFER_SIZE)
    {
        *str = ft_realloc(*str, (BUFFER_SIZE * i) + rd + 1);
        if (*str == NULL)
            return (-1);
        (*str)[(BUFFER_SIZE * i) + rd] = '\0';
        return (0);
    }
    chr_res = ft_strchr(*str, '\n');
    if (chr_res != NULL)
    {
        new_len = chr_res - *str + 1;
        *str = ft_realloc(*str, new_len + 1);
        if (*str == NULL)
            return (-1);
        chr_res = *str + (chr_res - *str); // Update chr_res to the new location
        *save = ft_strdup(chr_res + 1);
        (*str)[new_len] = '\0';
        return (0);
    }
    return (1);
}
