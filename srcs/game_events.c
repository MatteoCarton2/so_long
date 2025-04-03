/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:37:58 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/03 19:39:15 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* keycode Linux : 119 = W, 115 = S, 97 = A, 100 = D */
static void	get_new_position(int keycode, int *new_x, int *new_y, t_game *game)
{
	*new_x = game->map->player_x;
	*new_y = game->map->player_y;
	if (keycode == 119)
		(*new_y)--;
	else if (keycode == 115)
		(*new_y)++;
	else if (keycode == 97)
		(*new_x)--;
	else if (keycode == 100)
		(*new_x)++;
}

static int	is_valid_move(t_map *map, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= (int)map->width || new_y < 0
		|| new_y >= (int)map->height)
		return (0);
	if (map->map[new_y][new_x] == '1')
		return (0);
	if (map->map[new_y][new_x] == 'E' && map->collected != map->collectibles)
		return (0);
	return (1);
}

static void	check_win(t_game *game)
{
	if (game->map->map[game->map->player_y][game->map->player_x] == 'E')
	{
		ft_printf("Félicitations ! Vous avez gagné en %d coups!\n",
			game->map->moves);
		exit_game(game);
	}
}

/* remplacer l'ancienne position du joueur (player x et y car on les a tjr
pas mis à jour. Par 'O' (car y'a plus rien désormais)) */
static void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map->map[game->map->player_y][game->map->player_x] = '0';
	game->map->player_x = new_x;
	game->map->player_y = new_y;
	if (game->map->map[game->map->player_y][game->map->player_x] == 'C')
		game->map->collected++;
	ft_printf("Total moves : %d\n", ++game->map->moves);
	check_win(game);
	game->map->map[game->map->player_y][game->map->player_x] = 'P';
}

int	handle_key(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;
	size_t	x;
	size_t	y;

	if (keycode == 65307)  /* Touche Échap */
		exit_game(game);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
	{
		get_new_position(keycode, &new_x, &new_y, game);
		if (is_valid_move(game->map, new_x, new_y))
		{
			update_player_position(game, new_x, new_y);
			/* On redessine la carte case par case */
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
	}
	return (1);
}
