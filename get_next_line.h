/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquiroga <mquiroga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:21:09 by cyberoot          #+#    #+#             */
/*   Updated: 2022/11/03 11:32:53 by mquiroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
//# define BUFFER_SIZE 1

typedef struct s_cache
{
	char			buffer[BUFFER_SIZE + 1];
	int				fd;
	int				nread;
	struct s_cache	*next;
}					t_cache;

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char **line_free, char *cache_content);
size_t	ft_strlen(const char *s);

#endif