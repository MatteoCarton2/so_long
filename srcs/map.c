/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:27:35 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/26 11:44:18 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// ENLEVER LES DEBUG
//voir si il faut garder le \n dans le ft_strlen ou pas

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
    map->width = (ft_strlen(line) - 1); // on stocke la longueur (on enlève le \n)
    map->height = 1; // première ligne (on va ensuite ajouter ++ à chaque ligne pour compter la hauteur)
    free (line);
    line = get_next_line(fd);
    while (line != NULL)
    {
        // vérifier que la ligne à la même longueur
        if ((ft_strlen(line) - 1) != map->width) // on elève le \n
        {
            free(line);
            return (0);
        }
        map->height++;
        free(line);
        line = get_next_line(fd); // lire la ligne suivante
    }
    if (map->height >= map->width)
        {
            ft_printf("On a pas un rectangle !\n"); // debug
            return (0);
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
    printf("Nombre de P : %d | Nombre de C : %d | Nombre de E : %d\n", P_counter, C_counter, E_counter); // DEBUG
    if (P_counter != 1 || E_counter != 1 || C_counter < 1)
        return (0);
    map->collectibles = C_counter;
    return (1);
}

int store_map(char *filename, t_map *map) {
    int fd;
    size_t i;
    size_t j;
    char *line;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    map->map = malloc(sizeof(char *) * map->height); // initialisation
    map->map_copy = malloc(sizeof(char *) * map->height);
    if(!map->map || !map->map_copy)
        return (0);
    i = 0;
    while (i < map->height)
    {
        j = 0;
        map->map[i] = malloc(sizeof(char) * map->width + 1); // +1 pour le \0
        map->map_copy[i] = malloc(sizeof(char) * map->width + 1);
        line = get_next_line(fd);
        while (line[j] != '\0')
        {
            map->map[i][j] = line[j];
            map->map_copy[i][j] = line[j];
            j++;
        }
        free(line);
        i++;
    }
    close(fd);
    
    // DEBUG

    ft_printf("Carte stockée :\n");
    i = 0;
    while (i < map->height)
    {
        ft_printf("%s", map->map[i]);
        i++;
    }
    
    // FIN DEBUG

    return (1);
}