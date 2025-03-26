/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:54:07 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/26 14:26:04 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int init_game(t_game *game, t_map *map)
{
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
    game->width = map->width * 16;
    game->height = map->height * 16;

    if (!create_window(game, map))
        return (printf("create_window failed\n"), 0);
    
    if (!load_sprites(game))
        return (printf("load_sprites failed\n"), 0);
    
    if (!draw_map(game, map))
        return (printf("draw_map failed\n"), 0);

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

    width = 16;
    height = 16;    
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
            mlx_put_image_to_window(game->mlx, game->win, game->wall, x * 16, y * 16);
        if (map->map[y][x] == '0') // afficher floor
            mlx_put_image_to_window(game->mlx, game->win, game->floor, x * 16, y * 16);
        if (map->map[y][x] == 'P')  // afficher player
            mlx_put_image_to_window(game->mlx, game->win, game->player, x * 16, y * 16);
        if (map->map[y][x] == 'C')  // afficher collect
            mlx_put_image_to_window(game->mlx, game->win, game->collect, x * 16, y * 16);
        if (map->map[y][x] == 'E')  // afficher exit
            mlx_put_image_to_window(game->mlx, game->win, game->exit, x * 16, y * 16);
        x++;
       }
       y++; 
    }
    return (1);
}