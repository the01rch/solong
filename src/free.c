/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:08:59 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 20:00:22 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

int	free_exit(t_data *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
	mlx_destroy_image(game->mlx, game->player);
	mlx_destroy_image(game->mlx, game->exit);
	mlx_destroy_image(game->mlx, game->cards);
	mlx_destroy_image(game->mlx, game->floor);
	mlx_destroy_image(game->mlx, game->player_left);
	mlx_destroy_image(game->mlx, game->wall);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

void	free_visited(int **visited, t_data *game)
{
	int	y;

	y = 0;
	while (y < game->height)
		free(visited[y++]);
	free(visited);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}
