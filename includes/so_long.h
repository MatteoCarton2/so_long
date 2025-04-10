/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:00:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/09 21:27:10 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <fcntl.h>

typedef struct s_map
{
	size_t	height;
	size_t	width;
	char	**map;
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		collectibles;
	int		collected;
	int		p_counter;
	int		e_counter;
	int		c_counter;
	int		moves;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	int		width;
	int		height;
	void	*wall;
	void	*player;
	void	*collect;
	void	*exit;
	void	*floor;
	t_map	*map;
}			t_game;

// map_load.c
int			validate_map(char *filename, t_map *map);
int			store_map(char *filename, t_map *map);
int			count_elements(char *filename, t_map *map);

// map_check.c
int			check_extension(char *filename);
int			check_rectangle(char *filename, t_map *map);
int			check_walls(t_map *map);
void		free_map_resources(t_map *map, size_t current_row, char *line,
				int fd);
int			count_line_elements(char *line, t_map *map);

// path.c
int			check_path(t_map *map);

// game_init.c
int			init_game(t_game *game, t_map *map);
int			load_sprites(t_game *game);
int			draw_map(t_game *game, t_map *map);
int			exit_game(t_game *game);
int			put_image(t_game *game, char tile, size_t x, size_t y);

// game_events.c
int			handle_key(int keycode, t_game *game);

// utils.c
int			open_and_get_line(char *filename, char **line);
int			find_player(t_map *map);
int			find_exit(t_map *map);
void		redraw_map(t_game *game);
void		handle_error(char *error_message);
void		clear_gnl_buffer(int fd);

// utils_2.c
void		free_resources(t_game *game);
