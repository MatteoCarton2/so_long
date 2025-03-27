/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:13:09 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/27 18:54:16 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
// objets à collecter = C
// sortie = E
// position de départ perso = P
// vide = 0
// murs = 1


int main(int argc, char **argv) {

    t_map map;
    t_game game;
    
    if (argc != 2)
    {
        ft_printf("Error\nWrong number of arguments ❌\n");
        return (1);
    }
    if (validate_map(argv[1], &map) == 0)
        return (1);
    if (check_path(&map) == 0)
    {
        ft_printf("Error\nNo valid path found ❌\n");
        return (1);
    }
    ft_printf("Chemin faissable 🏆\n");
        
    ft_printf("Width: %d\n", map.width);
    ft_printf("Height: %d\n", map.height);
    ft_printf("Carte Valide ✅");


    // GAME

    
    if (init_game(&game, &map) == 0)
    {
        ft_printf("Error\nFailed to initialize game ❌\n");
        return (1);
    }
    mlx_loop(game.mlx); // diff entre game.mlx et game->mlx
    return (0);
}