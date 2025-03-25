/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:13:09 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/25 14:01:32 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
// personnage = P
// objets à collecter = C
// sortie = P
// vide = 0
// murs = 1


int main(int argc, char **argv) {

    t_map map;
    
    if (argc != 2)
    {
        ft_printf("Error\nWrong number of arguments !\n");
        return (1);
    }
    if (check_extension(argv[1]) == 0)
    {
        ft_printf("Error\nNot a .ber map !\n");
        return (1);
    }
    if (read_map(argv[1], &map) == 0)
    {
        ft_printf("Error\nNot a valide map !\n");
        return (1);
    }

    ft_printf("Width: %d\n", map.width);
    ft_printf("Height: %d\n", map.height);
    return (0);
}