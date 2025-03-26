/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:54:07 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/26 12:16:39 by mcarton          ###   ########.fr       */
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
        return (0);
    
    // Calculer la taille de la fenêtre (32 pixels par case)
    game->width = map->width * 32;
    game->height = map->height * 32;

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