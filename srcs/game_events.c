/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:37:58 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/28 11:31:09 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void get_new_position(int keycode, int *new_x, int *new_y, t_game *game)
{
    *new_x = game->map->player_x;
    *new_y = game->map->player_y;
    
    if (keycode == 13)      // W (haut)
        (*new_y)--;
    else if (keycode == 1)  // S (bas)
        (*new_y)++;
    else if (keycode == 0)  // A (gauche)
        (*new_x)--;
    else if (keycode == 2)  // D (droite)
        (*new_x)++;
}


static int is_valid_move(t_map *map, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= (int)map->width || new_y < 0 || new_y >= (int)map->height) // si c'est en dehors des limites
        return (0);
    if (map->map[new_y][new_x] == '1') // si c'est un mur
        return (0);
    if (map->map[new_y][new_x] == 'E' && map->collected != map->collectibles) // si on est à la sortie mais qu'on a pas récup tous les collectibles, pas possible
        return (0);
    return (1);
}

static void check_win(t_game *game)
{
    if (game->map->map[game->map->player_y][game->map->player_x] == 'E')
    {
        ft_printf("Félicitations ! Vous avez gagné en %d coups!\n", game->map->moves);
        exit_game(game);
    }
}

static void update_player_position(t_game *game, int new_x, int new_y)
{
    // remplacer l'ancienne position du joueur (player x et y car on les a tjr 
    // pas mis à jour. Par 'O' (car y'a plus rien désormais))
    game->map->map[game->map->player_y][game->map->player_x] = '0';
    game->map->player_x = new_x;
    game->map->player_y = new_y;
    
    if (game->map->map[game->map->player_y][game->map->player_x] == 'C')
        game->map->collected++;
    
    ft_printf("Total moves : %d\n", ++game->map->moves);
    check_win(game);
    game->map->map[game->map->player_y][game->map->player_x] = 'P';
}

int handle_key(int keycode, t_game *game) // printf la pos new_x et new_y
{
    int new_x;
    int new_y;
    
    if (keycode == 53)  // ESC
        exit_game(game);
    
    if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
    {
        get_new_position(keycode, &new_x, &new_y, game);
        if (is_valid_move(game->map, new_x, new_y))
        {
            update_player_position(game, new_x, new_y);
            draw_map(game, game->map);
        }
    }
    return (1);
}
