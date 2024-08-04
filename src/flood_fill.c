/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 02:55:42 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 18:21:52 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

static int	**init_visited(t_data *game)
{
	int	**visited;
	int	y;

	y = 0;
	visited = ft_calloc(game->height, sizeof(int *));
	if (!visited)
		return (NULL);
	while (y < game->height)
	{
		visited[y] = ft_calloc(game->width, sizeof(int));
		if (!visited[y])
		{
			free_visited(visited, game);
			fd_putstr("Error\nMemory allocation error", 2);
		}
		y++;
	}
	return (visited);
}

static void	check_cards(t_data *game, int **visited)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (!visited[y][x] && (game->map[y][x] == 'E'
				|| game->map[y][x] == 'C'))
			{
				free_visited(visited, game);
				fd_putstr(
					"Error\nUnreachability for cards or exit\n", 2);
				free_exit(game);
			}
			x++;
		}
		y++;
	}
}

static void	flood_fill(t_data *game, int **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height)
		return ;
	if (visited[y][x] || game->map[y][x] == '1')
		return ;
	visited[y][x] = 1;
	flood_fill(game, visited, x - 1, y);
	flood_fill(game, visited, x + 1, y);
	flood_fill(game, visited, x, y - 1);
	flood_fill(game, visited, x, y + 1);
}

void	is_reachable(t_data *game)
{
	int	**visited;

	visited = NULL;
	visited = init_visited(game);
	flood_fill(game, visited, game->px, game->py);
	check_cards(game, visited);
	free_visited(visited, game);
}
