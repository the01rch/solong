/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 02:56:57 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 20:01:26 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	char	**map;
	void	*player;
	void	*player_left;
	void	*cards;
	void	*exit;
	void	*floor;
	void	*wall;
	int		tcards;
	int		texit;
	int		ccards;
	int		moves;
	int		row;
	int		px;
	int		py;
	int		size_yimg;
	int		size_ximg;
	int		width;
	int		height;
}	t_data;

void		init_game(t_data *game);

char		*get_next_line(int fd);

void		fd_putstr(char *str, int fd);

void		*ft_calloc(size_t count, size_t size);

void		is_reachable(t_data *game);

void		fd_putstr(char *s, int fd);

int			ft_strlen(char *str);

void		ft_putnbr(int n);

void		gest_err(t_data *game);

int			handler_keycode(int keycode, t_data *game);

void		get_player_pos(t_data *game);

void		count_cols(t_data *game);

void		free_map(char **map);

int			free_exit(t_data *game);

void		fill_map(char *av, t_data *game);

void		free_visited(int **visited, t_data *game);

void		display_choices(t_data *game, size_t x, size_t y);

void		display_map(t_data *game);

#endif
