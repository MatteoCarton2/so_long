/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:27:35 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/27 22:53:29 by mcarton          ###   ########.fr       */
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

int validate_map(char *filename, t_map *map)
{
    int P_counter;
    int E_counter;
    int C_counter;

    P_counter = 0;
    E_counter = 0;
    C_counter = 0;
    if (!check_extension(filename))
        return (ft_printf("Error\n❌ Invalid file extension. Must be .ber\n"), 0);
    if (!check_rectangle(filename, map))
        return (ft_printf("Error\n❌ Map must be rectangular\n"), 0);
    if (!check_walls(map))
        return (ft_printf("Error\n❌ Map must be surrounded by walls\n"), 0);
    if (!count_elements(filename, map, &P_counter, &E_counter, &C_counter))
        return (ft_printf("Error\n❌ Invalid map elements configuration\n"), 0);
    if (!store_map(filename, map))
        return (ft_printf("Error\n❌ Failed to store map in memory\n"), 0);
    return (1);
}

int store_map(char *filename, t_map *map) {
    int fd;
    char *line;
    size_t i;
    
    fd = open_and_get_line(filename, &line);
    if (fd == -1)
        return (0);
    map->map = malloc(sizeof(char *) * map->height); // initialisation
    map->map_copy = malloc(sizeof(char *) * map->height); // pour la copie
    if(!map->map || !map->map_copy)
        return (0);
    i = 0;
    while (i < map->height)
    {
       store_map_line(line, map, i);
        free(line);
        i++;
        line = get_next_line(fd);
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

static void store_map_line(char *line, t_map *map, size_t i)
{
    size_t j;

    j = 0;
    map->map[i] = malloc(sizeof(char) * map->width + 1); // +1 pour le \0
    map->map_copy[i] = malloc(sizeof(char) * map->width + 1);
    while (line[j] != '\0')
    {
        map->map[i][j] = line[j];
        map->map_copy[i][j] = line[j];
        j++;
    }
}

int count_elements(char *filename, t_map *map, int *P_counter, int *E_counter, int *C_counter)
{
    char *line;
    int fd;

    fd = open_and_get_line(filename, &line);
    if (fd == -1)
        return (0);
    while (line != NULL)
    {
        if (count_line_elements(line, P_counter, E_counter, C_counter) == 0)
            return (free(line), 0);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    printf("Nombre de P : %d | Nombre de C : %d | Nombre de E : %d\n", P_counter, C_counter, E_counter); // DEBUG
    if (P_counter != 1 || E_counter != 1 || C_counter < 1)
        return (0);
    map->collectibles = C_counter;
    return (1);
}

static int count_line_elements(char *line, int *P_counter, int *E_counter, int *C_counter)
{
    int i;

    i = 0;
    while (line[i] != '\n')
    {
        if (line[i] == 'P')
            (*P_counter)++;
        else if (line[i] == 'E')
            (*E_counter)++;
        else if (line[i] == 'C')
            (*C_counter)++;
        else if (line[i] != '0' && line[i] != '1' && line[i] != '\n')
            {
                free(line);
                return (0);
            }
        i++;
    }
    return (1);
}
