/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:54:07 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/27 13:36:18 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int init_game(t_game *game, t_map *map)
{
    game->map = map;
    map->collected = 0;
    map->moves = 0;
    /* mlx init = fonction qui prépare tout ce dont on a besoin pour faire des graphismes. 
    1. Alloue de la mémoire pour :
        La connexion au système graphique de notre OS
        Les buffers pour les images
        La gestion des événements
    2. Initialise :
        La connexion avec le système d'affichage
        Les structures de données pour les images
        Les structures pour gérer les événements (touches, souris)
    3. Retourne un pointeur vers tout ça 
    Programme → MiniLibX(mlx_init) → Système Graphique → GPU(carte graphique) → Écran */
    game->mlx = mlx_init();
    if (game->mlx == NULL)
        return (printf("mlx_init failed\n"), 0);
    
    // Calculer la taille de la fenêtre (16 pixels par case)
    game->width = map->width * 32;
    game->height = map->height * 32;

    if (!create_window(game, map))
        return (printf("create_window failed\n"), 0);
    
    if (!load_sprites(game))
        return (printf("load_sprites failed\n"), 0);
    
    if (!draw_map(game, map))
        return (printf("draw_map failed\n"), 0);
    
    // mlx_key_hook = fonction qui dit à MiniLibX "quand une touche est pressée, appelle cette fonction"
    //   mlx_key_hook(fenêtre, fonction_à_appeler, données_à_passer)
    /* mlx_key_hook est conçue pour être un "callback" (une fonction qui est appelée automatiquement). 
    Dans ce type de système, on ne peut généralement passer qu'un nombre limité de paramètres.
    C'est comme si MiniLibX disait :
    "Je peux appeler ta fonction, mais je ne peux lui passer que :
    1. Le code de la touche (keycode) (elle le fait automatiquement)
    2. Un SEUL paramètre de ton choix"
    C'est une limitation de la bibliothèque, pas de mon code, donc handle_key peut avoir que 2 paramètres 
    (en réalité 1 car on a besoin du key_code) */
    mlx_key_hook(game->win, handle_key, game);
    // Le 0 = event_mask, c'est comme un sous-type à l'évènement d'avant (mais pour 17, y'a rien donc on met 0 pour respecter la convention)
    mlx_hook(game->win, 17, 0, exit_game, game); // 17 : DestroyNotify (fermeture fenêtre)
    return (1);
}

int create_window(t_game *game, t_map *map)
{
    (void)map;
    /* mlx_new_window() créer une fenêtre sur notre écran, on a besoin de savoir où 
    est notre fenêtre en mémoire car toutes les autres fonctions MiniLibX ont besoin
    de ce ptr pour : dessiner dans la fenêtre, gérer les clics, touches, fermer la fenêtre, ... */
    game->win = mlx_new_window(game->mlx, game->width, game->height, "So_long");
    if (game->win == NULL)
        return (0);
    return (1);
}

int load_sprites(t_game *game)
{
    int width;
    int height;

    width = 32;
    height = 32;    
    game->collect = mlx_xpm_file_to_image(game->mlx, "sprites/collect.xpm", &width, &height);
    if (game->collect == NULL)
        return (printf("collect.xpm failed\n"), 0);
    game->exit = mlx_xpm_file_to_image(game->mlx, "sprites/exit.xpm", &width, &height);
    if (game->exit == NULL)
        return (printf("exit.xpm failed\n"), 0);
    game->floor = mlx_xpm_file_to_image(game->mlx, "sprites/floor.xpm", &width, &height);
    if (game->floor == NULL)
        return (printf("floor.xpm failed\n"), 0);
    game->player = mlx_xpm_file_to_image(game->mlx, "sprites/player.xpm", &width, &height);
    if (game->player == NULL)
        return (printf("player.xpm failed\n"), 0);
    game->wall = mlx_xpm_file_to_image(game->mlx, "sprites/wall.xpm", &width, &height);
    if (game->wall == NULL)
        return (printf("wall.xpm failed\n"), 0);
    return (1);
}

int draw_map(t_game *game, t_map *map) // regarder si faut mettre des vérifs (check si mlxputimage peut fail)
{
    size_t y;
    size_t x;
    
    y = 0;
    while (y < map->height)
    {
       x = 0;
       while (x < map->width)
       {
        if (map->map[y][x] == '1') // afficher wall
            mlx_put_image_to_window(game->mlx, game->win, game->wall, x * 32, y * 32);
        if (map->map[y][x] == '0') // afficher floor
            mlx_put_image_to_window(game->mlx, game->win, game->floor, x * 32, y * 32);
        if (map->map[y][x] == 'P')  // afficher player
            mlx_put_image_to_window(game->mlx, game->win, game->player, x * 32, y * 32);
        if (map->map[y][x] == 'C')  // afficher collect
            mlx_put_image_to_window(game->mlx, game->win, game->collect, x * 32, y * 32);
        if (map->map[y][x] == 'E')  // afficher exit
            mlx_put_image_to_window(game->mlx, game->win, game->exit, x * 32, y * 32);
        x++;
       }
       y++; 
    }
    return (1);
}

int handle_key(int keycode, t_game *game)
{
    int new_x = game->map->player_x;
    int new_y = game->map->player_y;
    int is_movement_key;

    is_movement_key = 0;
    if (keycode == 53) // = ESC
        exit(0);
    
    if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
        is_movement_key = 1;
    
    if (keycode == 13)  // W (haut)
        new_y--;
    
    if (keycode == 1)   // S (bas)
        new_y++;
    
    if (keycode == 0)   // A (gauche)
        new_x--;
    
    if (keycode == 2)   // D (droite)
        new_x++;
    
    /* Comme l'appel a handle_key depuis mlx_key_hook ne peut avoir que 2 paramètres (keycode + 1 au choix), 
    on accède aux données de la map depuis la struct de la game (qui contient un ptr vers la map)*/
    if(is_movement_key && is_valid_move(game->map, new_x, new_y) == 1)
    {
        // remplacer l'ancienne position du joueur (player x et y car on les a tjr 
        // pas mis à jour, par 'O' (car y'a plus rien désormais))
        game->map->map[game->map->player_y][game->map->player_x] = '0';
        // mettre à jour la nouvelle position de notre joueur
        game->map->player_x = new_x;
        game->map->player_y = new_y;
        
        if (game->map->map[game->map->player_y][game->map->player_x] == 'C') // si notre perso est sur un collectible
            game->map->collected++;
        
        ft_printf("Total moves : %d\n", ++game->map->moves);
        
        // Vérifier si on a gagné (sur la sortie avec tous les collectibles)
        if (game->map->map[game->map->player_y][game->map->player_x] == 'E')
        {
            ft_printf("Félicitations ! Vous avez gagné en %d coups!\n", game->map->moves);
            exit_game(game);
        }
        
        // mettre à jour la nouvelle case ou notre joueur est par 'P'
        game->map->map[game->map->player_y][game->map->player_x] = 'P';

        // On met à jour la map
        draw_map(game, game->map);
        
    }
    return (1);
}

int is_valid_move(t_map *map, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= (int)map->width || new_y < 0 || new_y >= (int)map->height) // si c'est en dehors des limites
        return (0);
    if (map->map[new_y][new_x] == '1') // si c'est un mur
        return (0);
    if (map->map[new_y][new_x] == 'E' && map->collected < map->collectibles) // si on est à la sortie mais qu'on a pas récup tous les collectibles, pas possible
        return (0);
    return (1);
}

int exit_game(t_game *game)
{
    size_t i;

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