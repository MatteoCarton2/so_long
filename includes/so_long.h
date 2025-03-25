/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:00:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/25 17:28:32 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fcntl.h>

typedef struct s_map
{
	size_t		height;		// hauteur de la carte
	size_t		width;		// largeur de la carte
	char	**map;		// la carte elle-même
    char    **map_copy; // copie de la carte pour l'algo
	int		player_x;	// position X du joueur
	int		player_y;	// position Y du joueur
	int		exit_x;		// position X de la sortie
	int		exit_y;		// position Y de la sortie
	int		collectibles;	// nombre d'objets à collecter
	int		collected;	// nombre d'objets collectés
	int		moves;		// nombre de mouvements
}	t_map;

// map.c
int check_extension(char *filename);
int read_map(char *filename, t_map *map);
int validate_map(char *filename, t_map *map);
int store_map(char *filename, t_map *map);

// path.c
int check_path(t_map *map);
int find_player_and_flood(t_map *map);
int check_exit_and_collectibles(t_map *map);
void flood_fill(t_map *map, size_t x, size_t y);