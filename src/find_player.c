/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:33:08 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 18:19:33 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

static bool	find_player(t_data *game, int x, int y)
{
	if (game->map[y][x] == 'P' || game->map[y][x] == 'L'
		|| game->map[y][x] == 'I' || game->map[y][x] == 'Y')
	{
		game->py = y;
		game->px = x;
		return (true);
	}
	return (false);
}

void	get_player_pos(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	if (game == NULL || game->map == NULL)
	{
		fd_putstr("Error\nThe game|map is NULL", 2);
		free_exit(game);
	}
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (find_player(game, x, y))
				return ;
			x++;
		}
		y++;
	}
	fd_putstr("Error\nNo player found on the map", 2);
	free_exit(game);
}

void	display_map(t_data *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			display_choices(game, x, y);
			x++;
		}
		y++;
	}
}
