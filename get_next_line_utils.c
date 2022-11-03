/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyberoot <cyberoot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:52:13 by cyberoot          #+#    #+#             */
/*   Updated: 2022/10/26 08:46:17 by cyberoot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (!(unsigned char)c)
		return (&((char *)s)[i]);
	return (NULL);
}

char	*ft_strjoin(char **line_free, char *cache_content)
{
	size_t	counter[2];
	size_t	i;
	size_t	j;
	char	*result;

	counter[0] = ft_strlen(*line_free);
	counter[1] = ft_strlen(cache_content);
	result = malloc(sizeof(char) * (counter[0] + counter[1] + 1));
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (i < counter[0])
	{
		result[i] = (*line_free)[i];
		i++;
	}
	j = 0;
	while (j < (counter[1]))
	{
		result[i + j] = (cache_content)[j];
		j++;
	}
	result[counter[0] + counter[1]] = '\0';
	return (free((*line_free)), free(cache_content), result);
}

char	*ft_substr(const char *s, unsigned int start, size_t end)
{
	char	*response;
	int		x[2];

	x[0] = ft_strlen(s);
	if (x[0] < (int)start)
		return (ft_strdup(""));
	if ((x[0] - start) < (end + 1))
		return (ft_strdup(s + start));
	response = malloc(sizeof(char) * (x[0] + 1));
	if (!response)
		return (NULL);
	x[1] = 0;
	while (x[1] < ((int)end + 1) && s[x[1]])
	{
		response[x[1]] = ((char *)s)[start + x[1]];
		x[1]++;
	}
	response[x[1]] = '\0';
	return (response);
}

char	*ft_strdup(const char *s)
{
	char	*response;
	int		i;
	int		size;

	size = 0;
	while (s[size])
		++size;
	response = malloc(sizeof(char) * (size + 1));
	if (!response)
		return (NULL);
	i = 0;
	while (*s)
	{
		response[i] = *s;
		s++;
		i++;
	}
	response[i] = '\0';
	return (response);
}
