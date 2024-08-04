/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:18:31 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 18:27:38 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

void	fd_putstr(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*str;
	size_t				i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
		str[i++] = (unsigned char) c;
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	total;

	tab = NULL;
	total = (count * size);
	if (count != 0 && ((count * size) / count != size))
		return (NULL);
	tab = malloc(total);
	if (tab == NULL)
		return (NULL);
	ft_memset(tab, 0, total);
	return (tab);
}
