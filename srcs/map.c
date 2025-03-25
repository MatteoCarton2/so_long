/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:27:35 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/25 14:01:27 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// personnage = P
// objets à collecter = C
// sortie = P
// vide = 0
// murs = 1

/* if valid = 1, if invalid = 0 */
int check_extension(char *filename) {
    
    int leng;

    leng = ft_strlen(filename);
    if (leng < 4)
        return (0);
    if (ft_strncmp(filename + (leng - 4), ".ber", 4) == 0)
        return (1);
    return (0);
}

int read_map(char *filename, t_map *map) {
    int fd;
    char *line;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    line = get_next_line(fd);
    if (!line)
        return (0);
    map->width = ft_strlen(line); // on stocke la longueur
    map->height = 1; // première ligne (on va ensuite ajouter ++ à chaque ligne pour compter la hauteur)
    free (line);
    line = get_next_line(fd);
    while (line != NULL)
    {
        // vérifier que la ligne à la même longueur
        if (ft_strlen(line) != map->width)
        {
            free(line);
            return (0);
        }
        map->height++;
        free(line);
        line = get_next_line(fd); // lire la ligne suivante
    }
    
    close(fd);
    return (1);
}


