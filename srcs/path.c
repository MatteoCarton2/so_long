/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:37:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/25 15:59:36 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* L'algo c'est comme si on verse l'eau à la case P et qu'on regarde ou elle 
peut aller (et si elle peut atteindre tous les collectibles et la sortie) */

int check_path(t_map *map) {
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
            }
            else if (map->map[y][x] == 'E')
            {
                printf("Position sortie trouvée, X : %zu et Y : %zu\n", x, y); // DEBUG
                map->exit_x = x;
                map->exit_y = y;
            }
            x++;
        }
        
        y++;
    }
    return (0);
}