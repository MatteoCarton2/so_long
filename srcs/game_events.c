/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:37:58 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/09 20:34:43 by mcarton          ###   ########.fr       */
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
		ft_printf("\n"
			"╔═════════════════════════════════════╗\n"
			"║           🏆  VICTORY!  🏆          ║\n"
			"║                                     ║\n"
			"║      You escaped in %d moves!       ║\n"
			"║                                     ║\n"
			"╚═════════════════════════════════════╝\n\n", game->map->moves);
		exit_game(game);
	}
}

/* replace the old player position (player_x and player_y because we haven't
updated them yet. With 'O' (because there's nothing there anymore)) */
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

	if (keycode == 65307)
		exit_game(game);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
	{
		get_new_position(keycode, &new_x, &new_y, game);
		if (is_valid_move(game->map, new_x, new_y))
		{
			update_player_position(game, new_x, new_y);
			redraw_map(game);
		}
	}
	return (1);
}
