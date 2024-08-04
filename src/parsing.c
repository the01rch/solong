/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:55:53 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 18:20:39 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

static int	count_rows(char *av, t_data *game)
{
	char	*str;
	int		fd;
	int		row;

	row = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (-1);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		row++;
	}
	free(str);
	close(fd);
	return (row);
}

void	count_cols(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (game == NULL)
	{
		fd_putstr("Error\nThe game|map is NULL\n", 2);
		free_exit(game);
	}
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '\n' || game->map[y][x] == ' ')
				game->map[y][x] = '\0';
			x++;
		}
		y++;
	}
	game->width = x;
}

static char	**allocate_map(t_data *game, char **map, int y)
{
	int		x;

	x = -1;
	map[y] = ft_calloc((ft_strlen(game->map[y]) + 1), sizeof(char));
	if (!map[y])
	{
		free_map(map);
		free_exit(game);
		return (NULL);
	}
	while (game->map[y][++x])
		map[y][x] = game->map[y][x];
	map[y][x] = 0;
	return (map);
}

static char	**del_null(t_data *game)
{
	char	**map;
	int		size;
	int		tmp;
	int		i;

	map = ft_calloc((game->height + 1), sizeof(char *));
	size = ft_strlen(game->map[0]);
	if (!map)
		return (0);
	i = 0;
	while (game->map[i])
	{
		tmp = ft_strlen(game->map[i]);
		if (tmp > 0 && tmp == size)
			map = allocate_map(game, map, i);
		else
		{
			free_map(map);
			fd_putstr("Error\nIncorrect game map !", 2);
			free_exit(game);
		}
		i++;
	}
	map[i] = NULL;
	return (free_map(game->map), map);
}

void	fill_map(char *av, t_data *game)
{
	char	*str;
	char	*tmp;
	int		fd;
	int		i;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return ;
	game->height = count_rows(av, game);
	game->map = ft_calloc((game->height + 1), sizeof(char *));
	if (!game->map)
		return ;
	i = 0;
	game->map[i] = get_next_line(fd);
	while (game->map[i++])
		game->map[i] = get_next_line(fd);
	close(fd);
	count_cols(game);
	game->map = del_null(game);
}
