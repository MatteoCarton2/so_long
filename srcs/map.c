/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:27:35 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/25 14:48:19 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// objets à collecter = C
// sortie = E
// position de départ perso = P
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

int validate_map(char *filename, t_map *map) {
    int fd;
    int P_counter;
    int E_counter;
    int C_counter;
    char *line;
    int i;

    
    P_counter = 0;
    E_counter = 0;
    C_counter = 0;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    line = get_next_line(fd);
    while (line != NULL)
    {
        i = 0;
        ft_printf("Ligne lue: %s", line); // DEBUG
        while(line[i] != '\0')
        {
            if (line[i] == 'P')
                P_counter++;
            else if (line[i] == 'E')
                E_counter++;
            else if (line[i] == 'C')
                C_counter++;
            else if (line[i] != '0' && line[i] != '1' && line[i] != '\n')
            {
                free(line);
                return (0);
            }
            i++;
        }
        free (line);
        line = get_next_line(fd);
    }
    close (fd);
    if (P_counter != 1 || E_counter != 1 || C_counter < 1)
        return (0);
    map->collectibles = C_counter;
    return (1);
}
