/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonanno <abonanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:28:32 by abonanno          #+#    #+#             */
/*   Updated: 2024/11/29 15:20:05 by abonanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char	*get_next_line(int fd)
{
    static char	*save;
    char		*str;
    char		*chr;
    ssize_t		rd;
    ssize_t		rd_total;

	if(fd < 0)
		return NULL;
    str = ft_calloc(1, BUFFER_SIZE + 1);
    if(str == NULL)
        return (NULL);
    if (save != NULL)
    {
		if(str)
            free(str);
        str = ft_strdup(save);
        if(str == NULL)
            return (NULL);
        free(save);
        save = NULL;
    }
    chr = ft_strchr(str, '\n');
    if(chr != NULL)
    {
        if(save)
            free(save);
        save = ft_strdup(&chr[1]);
        if(save == NULL)
            return (NULL);
        chr[1] = '\0';
        return (str);
    }
    rd_total = ft_strlen(str);
    str = ft_realloc(str, BUFFER_SIZE + rd_total + 1);
    if(str == NULL)
        return (NULL);
    rd = read(fd, &str[rd_total], BUFFER_SIZE);
	rd_total += rd;
    str = ft_realloc(str, BUFFER_SIZE + rd_total + 1);
    while(rd > 0)
    {
        chr = ft_strchr(str, '\n');
        if(chr != NULL)
        {
			if(save)
            	free(save);
            save = ft_strdup(&chr[1]);
            chr[1] = '\0';
			str = ft_realloc(str, ft_strlen(str) + 1);
            return (str);
        }
        rd = read(fd, &str[rd_total], BUFFER_SIZE);
        rd_total += rd;
        str = ft_realloc(str, BUFFER_SIZE + rd_total + 1);
        if(str == NULL)
            return (NULL);
    }
	if (rd == 0 && str[0] != '\0')
	{
		if(save)
			free(save);
		save = NULL;
		str = ft_realloc(str, ft_strlen(str) + 1);
		return (str);
	}
	if(rd == -1 || rd == 0)
	{
		free(str);
		return (NULL);
	}
	free(str);
    return NULL;
}

// int main()
// {
//     int fd = open("fd.txt", O_RDONLY);
//     char *str = get_next_line(fd);
//     while (str != NULL)
//     {
//         printf("%s", str);
//         free(str);
//         str = get_next_line(fd);
//     }
// 	free(str);
//     close(fd);
// }