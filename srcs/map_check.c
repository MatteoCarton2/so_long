/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:16:17 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/27 18:30:25 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int check_extension(char *filename) {
    
    int length;

    length = ft_strlen(filename);
    if (length < 4)
        return (0);
    if (ft_strncmp(filename + (length - 4), ".ber", 4) == 0)
        return (1);
    return (0);
}

int check_rectangle(char *filename, t_map *map)
{
    int fd;
    char *line;

    fd = open_and_get_line(filename, &line);
    if (fd == -1)
        return (0);
    map->width = (ft_strlen(line) - 1); // on stocke la longueur (on enlève le \n)
    map->height = 1; // première ligne (on va ensuite ajouter ++ à chaque ligne pour compter la hauteur)
    free (line);
    line = get_next_line(fd);
    while (line != NULL)
    {
        if ((ft_strlen(line) - 1) != map->width) // vérifier que la ligne à la même longueur et on elève le \n
            return(free(line), 0);
        map->height++;
        free(line);
        line = get_next_line(fd); // lire la ligne suivante
    }
    if (map->height > map->width)
        return (ft_printf("On a pas un rectangle !\n"), 0); // debug
    close(fd);
    return (1);
}

int check_walls(t_map *map)
{
   size_t i;

   i = 0;
   // Vérifier première et dernière ligne
   while (i < map->width)
   {
    if (map->map[0][i] != '1' || map->map[map->height - 1][i] != '1')
        return (0);
    i++;
    }
    
    // Vérifier première et dernière colonne
    i = 0;
    while (i < map->height)
    {
        if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}