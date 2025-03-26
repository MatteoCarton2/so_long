/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:37:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/26 16:28:55 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int check_path(t_map *map) {
    if (find_player_and_flood(map) == 0)
        return (0);
        
    // DEBUG - Afficher la carte map_copy
    
    ft_printf("\nCarte copy après flood_fill :\n");
    size_t i = 0;
    while (i < map->height)
    {
        ft_printf("%s", map->map_copy[i]);
        i++;
    }

    // FIN DEBUG 

    
    if (check_exit_and_collectibles(map) == 0)
        return (0);
    return (1);
}


int find_player_and_flood(t_map *map) {
    size_t y;
    size_t x;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->map[y][x] == 'P')
            {
                printf("Position joueur trouvée, X : %zu et Y : %zu\n", x, y); // DEBUG
                map->player_x = x;
                map->player_y = y;
                flood_fill(map, map->player_x, map->player_y);
                return (1);
            }
            x++;
        }
        y++;
    }
    return (0);
}

int check_exit_and_collectibles(t_map *map) {
    size_t y;
    size_t x;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->map[y][x] == 'E')
            {
                printf("Position sortie trouvée, X : %zu et Y : %zu\n", x, y); // DEBUG
                if (map->map_copy[y][x] != 'V') // il faut que la sortie sois accessible (donc = à V dans notre copie, sinon return (0)
                    return (0);
                map->exit_x = x;
                map->exit_y = y;
                
            }
            else if (map->map[y][x] == 'C') // même principe pour les collectibles
            {
                if (map->map_copy[y][x] != 'V')
                    return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}



/* L'algo c'est comme si on verse l'eau à la case P et qu'on regarde ou elle 
peut aller (et si elle peut atteindre tous les collectibles et la sortie) */

// V pour visited

void flood_fill(t_map *map, size_t x, size_t y)
{   
    // il faut que x et y sois dans la map
    if (x < map->width && y < map->height)
    {
        if (map->map_copy[y][x] == '1' || map->map_copy[y][x] == 'V')
            return;
        map->map_copy[y][x] = 'V'; // si la case n'as pas encore était visited, on met un V
        // ordre = haut, bas, gauche, droite
        flood_fill(map, x, y - 1);
        flood_fill(map, x, y + 1);
        flood_fill(map, x - 1, y);
        flood_fill(map, x + 1, y);
    }
}