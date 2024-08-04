/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 02:56:02 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 19:53:43 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

static void	print_moves(t_data *game)
{
	fd_putstr("Moves :", 1);
	ft_putnbr(game->moves);
	write(1, "\n", 1);
	display_map(game);
}

static void	update_ppos(t_data *game, int x, int y, char n)
{
	game->moves++;
	game->map[game->py][game->px] = '0';
	game->px = x;
	game->py = y;
	game->map[game->py][game->px] = n;
}

static void	move_x(t_data *game, int left)
{
	int	x;

	get_player_pos(game);
	if (left == 1)
		x = game->px - 1;
	else
		x = game->px + 1;
	if (x == game->width || game->map[game->py][x] == '1')
		return ;
	if (game->map[game->py][x] == 'C')
		game->ccards++;
	if (game->map[game->py][x] == 'E')
	{
		if (game->tcards == game->ccards)
			free_exit(game);
		else
			return ;
	}
	update_ppos(game, x, game->py, 'P');
	print_moves(game);
}

static void	move_y(t_data *game, int up)
{
	int	y;

	get_player_pos(game);
	if (up == 1)
		y = game->py - 1;
	else
		y = game->py + 1;
	if (y == game->height || game->map[y][game->px] == '1')
		return ;
	if (game->map[y][game->px] == 'C')
		game->ccards++;
	if (game->map[y][game->px] == 'E')
	{
		if (game->tcards == game->ccards)
			free_exit(game);
		else
			return ;
	}
	if (game->map[game->py][game->px] == 'L')
		update_ppos(game, game->px, y, 'L');
	else
		update_ppos(game, game->px, y, 'P');
	print_moves(game);
}

int	handler_keycode(int keycode, t_data *game)
{
	if (keycode == UP || keycode == 119)
		move_y(game, 1);
	if (keycode == DOWN || keycode == 115)
		move_y(game, 0);
	if (keycode == LEFT || keycode == 97)
		move_x(game, 1);
	if (keycode == RIGHT || keycode == 100)
		move_x(game, 0);
	if (keycode == ESC)
		free_exit(game);
	if (keycode == 121)
	{
		get_player_pos(game);
		if (game->map[game->py][game->px] == 'P')
			game->map[game->py][game->px] = 'Y';
		if (game->map[game->py][game->px] == 'L')
			game->map[game->py][game->px] = 'I';
		display_map(game);
	}
	return (0);
}
