/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 02:56:18 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 19:44:28 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

void	init_textures(t_data *game)
{
	game->player = mlx_xpm_file_to_image(game->mlx,
			"./textures/yugi.xpm", &game->size_ximg, &game->size_yimg);
	game->player_left = mlx_xpm_file_to_image(game->mlx,
			"./textures/yugi_left.xpm", &game->size_ximg, &game->size_yimg);
	game->exit = mlx_xpm_file_to_image(game->mlx,
			"./textures/portal.xpm", &game->size_ximg, &game->size_yimg);
	game->cards = mlx_xpm_file_to_image(game->mlx,
			"./textures/card.xpm", &game->size_ximg, &game->size_yimg);
	game->floor = mlx_xpm_file_to_image(game->mlx,
			"./textures/empty.xpm", &game->size_ximg, &game->size_yimg);
	game->wall = mlx_xpm_file_to_image(game->mlx,
			"./textures/ywall.xpm", &game->size_ximg, &game->size_yimg);
	if (!game->player || !game->player_left || !game->exit
		|| !game->cards || !game->floor || !game->wall)
	{
		fd_putstr("Error\nImage not initialized properly.\n", 2);
		free_exit(game);
	}
}

void	display_choices(t_data *game, size_t x, size_t y)
{
	if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx,
			game->mlx_win, game->player, (x * 64), (y * 64));
	if (game->map[y][x] == 'L')
		mlx_put_image_to_window(game->mlx,
			game->mlx_win, game->player_left, (x * 64), (y * 64));
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx,
			game->mlx_win, game->cards, (x * 64), (y * 64));
	else if (game->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx,
			game->mlx_win, game->exit, (x * 64), (y * 64));
	else if (game->map[y][x] == '0')
		mlx_put_image_to_window(game->mlx,
			game->mlx_win, game->floor, (x * 64), (y * 64));
	else if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx,
			game->mlx_win, game->wall, (x * 64), (y * 64));
}

void	init_game(t_data *game)
{
	game->mlx = mlx_init();
	init_textures(game);
	count_cols(game);
	get_player_pos(game);
	gest_err(game);
	is_reachable(game);
	game->mlx_win = mlx_new_window(game->mlx, game->width * 64,
			game->height * 64, "so_long");
	display_map(game);
	mlx_hook(game->mlx_win, 17, (1L << 17), free_exit, game);
	mlx_key_hook(game->mlx_win, handler_keycode, game);
	mlx_loop(game->mlx);
}
