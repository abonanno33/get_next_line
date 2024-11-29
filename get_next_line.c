/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonanno <abonanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:28:32 by abonanno          #+#    #+#             */
/*   Updated: 2024/11/30 00:45:11 by abonanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static char	*initialize_and_allocate(char **str)
{
	*str = NULL;
	*str = ft_realloc((unsigned char *)*str, BUFFER_SIZE + 1);
	if (*str == NULL)
		return (NULL);
	return (*str);
}

static char	*handle_saved_data(char **save, char **str)
{
	char	*chr;

	if (*save != NULL)
	{
		free(*str);
		*str = ft_strdup(*save);
		if (*str == NULL)
			return (NULL);
		free(*save);
		*save = NULL;
	}
	chr = ft_strchr(*str, '\n');
	if (chr != NULL)
	{
		*save = ft_strdup(&chr[1]);
		if (*save == NULL)
			return (NULL);
		chr[1] = '\0';
		return (*str);
	}
	return (NULL);
}

static char	*read_from_fd(int fd, char **str, char **save, ssize_t rd_total)
{
	ssize_t	rd;
	char	*chr;

	rd = read(fd, &(*str)[rd_total], BUFFER_SIZE);
	rd_total += rd;
	*str = ft_realloc((unsigned char *)*str, BUFFER_SIZE + rd_total + 1);
	while (rd > 0)
	{
		chr = ft_strchr(*str, '\n');
		if (chr != NULL)
		{
			*save = ft_strdup(&chr[1]);
			if (*save == NULL)
				return (NULL);
			chr[1] = '\0';
			*str = ft_realloc((unsigned char *)*str, ft_strlen(*str) + 1);
			return (*str);
		}
		rd = read(fd, &(*str)[rd_total], BUFFER_SIZE);
		rd_total += rd;
		*str = ft_realloc((unsigned char *)*str, BUFFER_SIZE + rd_total + 1);
		if (*str == NULL)
			return (NULL);
	}
	return (NULL);
}

static char	*finalize_result(char **str, char **save, ssize_t rd)
{
	if (rd == 0 && (*str)[0] != '\0')
	{
		if (*save)
			free(*save);
		*save = (NULL);
		*str = ft_realloc((unsigned char *)*str, ft_strlen(*str) + 1);
		return (*str);
	}
	if (rd == -1 || rd == 0)
	{
		free(*str);
		*str = NULL;
		if (*save)
		{
			free(*save);
			*save = NULL;
		}
		return (NULL);
	}
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save[4064];
	char		*str;
	char		*result;
	ssize_t		rd_total;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = initialize_and_allocate(&str);
	if (str == NULL)
		return (NULL);
	result = handle_saved_data(&save[fd], &str);
	if (result != NULL)
		return (result);
	rd_total = ft_strlen(str);
	str = ft_realloc((unsigned char *)str, BUFFER_SIZE + rd_total + 1);
	if (str == NULL)
		return (NULL);
	result = read_from_fd(fd, &str, &save[fd], rd_total);
	if (result != NULL)
		return (result);
	return (finalize_result(&str, &save[fd], 0));
}
t 