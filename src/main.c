/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 02:56:29 by redrouic          #+#    #+#             */
/*   Updated: 2024/08/04 19:45:38 by redrouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/so_long.h"

static void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		fd_putstr(map[i], 1);
		fd_putstr("\n", 1);
		i++;
	}
}

static bool	valid_fd(char **av)
{
	char	buff[1];
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0 || read(fd, buff, 1) == -1)
	{
		fd_putstr("Error\nUnable to open file\n", 2);
		if (fd >= 0)
			close(fd);
		exit(0);
	}
	close(fd);
	return (true);
}

static bool	valid_extension(char *filename)
{
	char	*ext;
	int		size;
	int		i;

	i = 0;
	ext = ".ber";
	size = ft_strlen(filename);
	if (size < 5)
		return (false);
	size -= 4;
	while (i < 4)
	{
		if (ext[i] != filename[size + i])
			return (false);
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	static t_data	game = {0};
	int				i;

	i = 0;
	if (ac != 2)
	{
		fd_putstr("Error\nUsage -> ./so_long [path/to/map.ber]\n", 2);
		return (0);
	}
	else if (valid_extension(av[1]))
	{
		valid_fd(av);
		fill_map(av[1], &game);
		if (!game.map)
		{
			fd_putstr("Error\nUnable to fill the map\n", 2);
			return (0);
		}
		print_map(game.map);
		init_game(&game);
	}
	else
		fd_putstr("Error\nFile extension name error\n", 2);
	return (0);
}
