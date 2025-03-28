/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:00:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/28 11:11:44 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../mlx/minilibx_opengl_20191021/mlx.h"
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

typedef struct s_game
{
    void    *mlx;       // connexion à la MiniLibX
    void    *win;       // la fenêtre
    void    *img;       // les image
    int     width;      // largeur de la fenêtre
    int     height;     // hauteur de la fenêtre
    void    *wall;      // image du mur
    void    *player;    // image du joueur
    void    *collect;   // image du collectible
    void    *exit;      // image de la sortie
    void    *floor;     // image du sol
    t_map   *map;       // pointeur vers la map
} t_game;

// map.c
int validate_map(char *filename, t_map *map);
int store_map(char *filename, t_map *map);
int count_elements(char *filename, t_map *map, int *P_counter, int *E_counter, int *C_counter);

//map_check.c
int check_extension(char *filename);
int check_rectangle(char *filename, t_map *map);
int check_walls(t_map *map);


// path.c
int check_path(t_map *map);
int check_exit_and_collectibles(t_map *map);
void flood_fill(t_map *map, size_t x, size_t y);
void flood_fill_without_exit(t_map *map, size_t x, size_t y);

// game_init.c
int init_game(t_game *game, t_map *map);
int load_sprites(t_game *game);
int draw_map(t_game *game, t_map *map);
int exit_game(t_game *game);

// game_events.c
int handle_key(int keycode, t_game *game);

// utils.c

int open_and_get_line(char *filename, char **line);
int find_player(t_map *map);
int find_exit(t_map *map);