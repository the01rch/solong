/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 21:12:40 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 18:26:29 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

static bool	is_rectangular(t_data *game)
{
	int		i;
	int		first_row_length;
	int		row_length;

	i = 1;
	first_row_length = ft_strlen(game->map[0]);
	while (i < game->height)
	{
		row_length = ft_strlen(game->map[i]);
		if (first_row_length != row_length)
			return (false);
		i++;
	}
	return (true);
}

static bool	valid_walls(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < game->width)
	{
		if (game->map[0][x] != '1' || game->map[game->height - 1][x] != '1')
			return (false);
		x++;
	}
	while (y < game->height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->width - 1] != '1')
			return (false);
		y++;
	}
	return (true);
}

int	check_counts(t_data *game, int *cplayer, int x, int y)
{
	if (game->map[y][x] == 'C')
		return (game->tcards++, 1);
	else if (game->map[y][x] == 'E')
		return (game->texit++, 1);
	else if (game->map[y][x] == 'P' || game->map[y][x] == 'L'
			|| game->map[y][x] == 'Y' || game->map[y][x] == 'I')
		return ((*cplayer)++, 1);
	else if (game->map[y][x] == '1')
		return (1);
	else if (game->map[y][x] == '0')
		return (1);
	return (0);
}

static int	valid_format(t_data *game)
{
	int	cplayer;
	int	x;
	int	y;

	cplayer = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!check_counts(game, &cplayer, x, y))
			{
				fd_putstr("Error\nInvalid character format.\n", 2);
				return (free_exit(game), 0);
			}
			x++;
		}
		y++;
	}
	if (game->texit != 1 || game->tcards == 0 || cplayer > 1)
		return (0);
	return (1);
}

void	gest_err(t_data *game)
{
	if (!is_rectangular(game))
	{
		fd_putstr("Error\nMap is not rectangular.\n", 2);
		return (free_exit(game), (void)0);
	}
	if (!valid_walls(game))
	{
		fd_putstr("Error\nWalls not surrounding.\n", 2);
		return (free_exit(game), (void)0);
	}
	if (valid_format(game) != 1)
	{
		fd_putstr("Error\nInvalid map format.\n", 2);
		return (free_exit(game), (void)0);
	}
}
