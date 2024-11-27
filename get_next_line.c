/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonanno <abonanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:28:32 by abonanno          #+#    #+#             */
/*   Updated: 2024/11/27 16:15:00 by abonanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char	*get_next_line(int fd)
{
    static char	*save = NULL;
    char		*str;
    ssize_t		rd;
    int			i;
    int			flag;

    i = 0;
    if (save == NULL)
        save = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    else
        save = realloc(save, BUFFER_SIZE + 1);
    if (save == NULL)
        return (NULL);
    if(strchr(save, '\n') != NULL)
    {
        str = ft_strdup(save);
        free(save);
        save = NULL;
        return (str);
    }
    if(save != NULL){
        str = strdup(save);
        free(save);
        save = NULL;
    }
    str = realloc(str, (BUFFER_SIZE + 1) + ft_strlen(str));
    if (str == NULL)
        return (NULL);
    rd = read(fd, &str[strlen((const char *) str)], BUFFER_SIZE);
    if (rd == 0)
    {
        free(str);
        return (NULL);
    }
    flag = 1;
    while (rd > 0 && flag == 1)
    {
        flag = app_get_next_line(&str, &save, rd, i);
        i++;
        if (flag == 1)
            rd = read(fd, &str[BUFFER_SIZE * i], BUFFER_SIZE);
    }
    if (str == NULL || flag == -1)
    {
        free(str);
        return (NULL);	
    }
    free(save);
    return str;
}

int main()
{
    int fd = open("fd.txt", O_RDONLY);
    char *str = get_next_line(fd);
    printf("%s",str);
    // while (str != NULL)
    // {
    //     free(str);
    //     str = get_next_line(fd);
    //     printf("%s", str);
    // }
    free(str);
    close(fd);
}