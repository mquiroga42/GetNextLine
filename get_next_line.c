/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquiroga <mquiroga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:21:44 by cyberoot          #+#    #+#             */
/*   Updated: 2022/11/03 11:32:54 by mquiroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_cache	*ini_cache(t_cache **cache, int fd)
{
	size_t	i;

	(*cache) = malloc(sizeof(t_cache));
	(*cache)->fd = fd;
	(*cache)->nread = 0;
	(*cache)->next = NULL;
	i = 0;
	while (i < BUFFER_SIZE)
	{
		(*cache)->buffer[i] = '\0';
		i++;
	}
	return (*cache);
}

void	clean_cache(t_cache **cache, int fd)
{
	t_cache	*tmp[2];
	int		i;

	tmp[0] = (*cache);
	tmp[1] = (*cache);
	while (tmp[0])
	{
		if (tmp[0]->fd == fd)
		{
			tmp[0]->fd = 0;
			i = -1;
			while (++i < BUFFER_SIZE)
				tmp[0]->buffer[i] = '\0';
			if (tmp[0]->next && tmp[0] != (*cache))
				tmp[1]->next = tmp[0]->next;
			else if (tmp[0] != (*cache))
				tmp[1]->next = NULL;
			else
				(*cache) = tmp[0]->next;
			free(tmp[0]);
			return ;
		}
		tmp[1] = tmp[0];
		tmp[0] = tmp[0]->next;
	}
}

char	*get_frag(char **line, char (*content)[BUFFER_SIZE + 1], int n_char)
{
	int	i;
	int	j;

	i = 0;
	while ((*content)[i] && (*content)[i] != '\n' && i < n_char)
		i++;
	if ((*content)[0] != '\0')
		(*line) = ft_strjoin(&(*line), ft_substr((*content), 0, i));
	j = 0;
	while (j < BUFFER_SIZE)
	{
		if (((i + j + 1) < BUFFER_SIZE)
			&& (*content)[i + j + 1]
				&& (i + j + 1) < n_char)
			(*content)[j] = (*content)[i + j + 1];
		else
			(*content)[j] = '\0';
		j++;
	}
	return ((*line));
}

t_cache	*get_cache(t_cache **cache, char **line, int fd)
{
	t_cache	*tmp;

	(*line) = ft_strdup("");
	if (!(*cache))
		return (ini_cache(&(*cache), fd));
	tmp = (*cache);
	while (tmp->fd != fd)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (tmp->fd == fd)
	{
		if (tmp->buffer[0] != '\0')
			(*line) = get_frag(&(*line), &(tmp->buffer), BUFFER_SIZE);
		if (!(*line))
			return (clean_cache(&(*cache), fd), NULL);
		return (tmp);
	}
	return (ini_cache(&(tmp->next), fd));
}

char	*get_next_line(int fd)
{
	static t_cache	*cache;
	t_cache			*now;
	char			*line;

	if (fd < 0 || read(fd, 0, 0))
		return (clean_cache(&cache, fd), NULL);
	now = get_cache(&cache, &line, fd);
	if (ft_strchr(line, '\n') || !now)
		return (line);
	while (true)
	{
		now->nread = read(fd, now->buffer, BUFFER_SIZE);
		now->buffer[now->nread] = '\0';
		if (now->nread != BUFFER_SIZE)
		{
			if (((!now->nread) | (now->nread == -1)) && !*line)
				return (free(line), clean_cache(&cache, fd), now = NULL, NULL);
			if (now->buffer[0] == '\0')
				return (clean_cache(&cache, fd), now = NULL, line);
			return (line = get_frag(&line, &(now->buffer), now->nread), line);
		}
		if (ft_strchr(now->buffer, '\n'))
			return (get_frag(&line, &(now->buffer), now->nread));
		line = ft_strjoin(&line, ft_substr(now->buffer, 0, (now->nread - 1)));
	}
}
