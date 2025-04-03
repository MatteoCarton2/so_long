/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:52 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/03 19:44:50 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	open_and_get_line(char *filename, char **line)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	*line = get_next_line(fd);
	if (!*line)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

int	find_player(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'P')
			{
				printf("Position joueur trouvée, X : %zu et Y : %zu\n", x, y);
				map->player_x = x;
				map->player_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	find_exit(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'E')
			{
				printf("Position sortie trouvée, X : %zu et Y : %zu\n", x, y);
				map->exit_x = x;
				map->exit_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	redraw_map(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			put_image(game, game->map->map[y][x], x, y);
			x++;
		}
		y++;
	}
	mlx_do_sync(game->mlx);
}
