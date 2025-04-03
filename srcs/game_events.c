/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:37:58 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/03 19:03:55 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* keycode 13 = W, 1 = S, 0 = A, 2 = D */
static void	get_new_position(int keycode, int *new_x, int *new_y, t_game *game)
{
	*new_x = game->map->player_x;
	*new_y = game->map->player_y;
	if (keycode == 13)
		(*new_y)--;
	else if (keycode == 1)
		(*new_y)++;
	else if (keycode == 0)
		(*new_x)--;
	else if (keycode == 2)
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

	if (keycode == 53)
		exit_game(game);
	if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
	{
		get_new_position(keycode, &new_x, &new_y, game);
		if (is_valid_move(game->map, new_x, new_y))
		{
			update_player_position(game, new_x, new_y);
			mlx_clear_window(game->mlx, game->win);
			draw_map(game, game->map);
			mlx_do_sync(game->mlx);
		}
	}
	return (1);
}
