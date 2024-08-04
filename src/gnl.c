/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 15:26:10 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 18:20:25 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static int	is_charset(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	ls1;
	size_t	ls2;
	size_t	i;
	size_t	y;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	new = malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (new == NULL)
		return (0);
	i = 0;
	while (i < ls1)
	{
		new[i] = s1[i];
		i++;
	}
	y = 0;
	while (y < ls2)
		new[i++] = s2[y++];
	new[i] = '\0';
	return (free(s1), new);
}

static char	*last_str(char	*src)
{
	char	*str;
	int		i;
	int		y;

	if (!src || !src[0])
		return (0);
	i = 0;
	while (src[i] != '\n' && src[i])
		i++;
	str = malloc(sizeof(char) * i + 2);
	if (str == NULL)
		return (0);
	y = 0;
	while (y <= i)
	{
		str[y] = src[y];
		y++;
	}
	str[y] = '\0';
	return (str);
}

static char	*move2left(char *str)
{
	char	*left;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
		return (free(str), NULL);
	left = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!left)
		return (free(left), NULL);
	j = 0;
	i++;
	while (str[i])
		left[j++] = str[i++];
	left[j] = '\0';
	return (free(str), left);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf;
	char		*line;
	int			bread;

	if (BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	bread = 1;
	while (!is_charset(str) && bread)
	{
		bread = read(fd, buf, BUFFER_SIZE);
		if (bread == -1)
			return (free(buf), NULL);
		buf[bread] = '\0';
		str = ft_strjoin(str, buf);
		if (!str)
			return (free(buf), NULL);
	}
	line = last_str(str);
	str = move2left(str);
	return (free(buf), line);
}
