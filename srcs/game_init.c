/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:54:07 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/03 19:44:23 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_game(t_game *game, t_map *map)
{
	game->map = map;
	map->collected = 0;
	map->moves = 0;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (printf("mlx_init failed\n"), 0);
	game->width = map->width * 32;
	game->height = map->height * 32;
	game->win = mlx_new_window(game->mlx, game->width, game->height, "So_long");
	if (game->win == NULL)
		return (printf("windows created failed\n"), 0);
	if (load_sprites(game) == 0)
		return (printf("load_sprites failed\n"), 0);
	if (draw_map(game, map) == 0)
		return (printf("draw_map failed\n"), 0);
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_loop(game->mlx);
	return (1);
}

/* w = weight, h = height*/
int	load_sprites(t_game *game)
{
	int	w;
	int	h;

	w = 32;
	h = 32;
	game->collect = mlx_xpm_file_to_image(game->mlx, "sprites/collect.xpm", &w,
			&h);
	if (game->collect == NULL)
		return (printf("collect.xpm failed\n"), 0);
	game->exit = mlx_xpm_file_to_image(game->mlx, "sprites/exit.xpm", &w, &h);
	if (game->exit == NULL)
		return (printf("exit.xpm failed\n"), 0);
	game->floor = mlx_xpm_file_to_image(game->mlx, "sprites/floor.xpm", &w, &h);
	if (game->floor == NULL)
		return (printf("floor.xpm failed\n"), 0);
	game->player = mlx_xpm_file_to_image(game->mlx, "sprites/player.xpm", &w,
			&h);
	if (game->player == NULL)
		return (printf("player.xpm failed\n"), 0);
	game->wall = mlx_xpm_file_to_image(game->mlx, "sprites/wall.xpm", &w, &h);
	if (game->wall == NULL)
		return (printf("wall.xpm failed\n"), 0);
	return (1);
}

int	put_image(t_game *game, char tile, size_t x, size_t y)
{
	if (tile == '1')
		return (mlx_put_image_to_window(game->mlx, game->win, game->wall, x
				* 32, y * 32));
	if (tile == '0')
		return (mlx_put_image_to_window(game->mlx, game->win, game->floor, x
				* 32, y * 32));
	if (tile == 'P')
		return (mlx_put_image_to_window(game->mlx, game->win, game->player, x
				* 32, y * 32));
	if (tile == 'C')
		return (mlx_put_image_to_window(game->mlx, game->win, game->collect, x
				* 32, y * 32));
	if (tile == 'E')
		return (mlx_put_image_to_window(game->mlx, game->win, game->exit, x
				* 32, y * 32));
	return (0);
}

int	draw_map(t_game *game, t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (put_image(game, map->map[y][x], x, y) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	exit_game(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map->height)
	{
		free(game->map->map[i]);
		i++;
	}
	free(game->map->map);
	if (game->mlx != NULL && game->wall != NULL)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->mlx != NULL && game->player != NULL)
		mlx_destroy_image(game->mlx, game->player);
	if (game->mlx != NULL && game->exit != NULL)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->mlx != NULL && game->floor != NULL)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->mlx != NULL && game->collect != NULL)
		mlx_destroy_image(game->mlx, game->collect);
	if (game->mlx != NULL && game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (1);
}
