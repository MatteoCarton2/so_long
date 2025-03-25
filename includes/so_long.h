/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:00:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/25 15:38:33 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fcntl.h>

typedef struct s_map
{
	size_t		height;		// hauteur de la carte
	size_t		width;		// largeur de la carte
	char	**map;		// la carte elle-même
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