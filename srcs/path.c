/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:37:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/27 23:09:55 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_path(t_map *map)
{
	size_t	i;

	if (find_player(map) == 0 || find_exit(map) == 0)
		return (0);
	map->map_copy[map->exit_y][map->exit_x] = '1';             
		// remplace la sortie par '1'
	flood_fill_without_exit(map, map->player_x, map->player_y);
		// check le cas spécial
	if (check_exit_and_collectibles(map) == 0)
		return (0);
	map->map_copy[map->exit_y][map->exit_x] = 'E';
	flood_fill(map, map->player_x, map->player_y);
	if (check_exit_and_collectibles(map) == 0)
		return (0);
	i = 0;
	while (i < map->height)
	{
		free(map->map_copy[i]);
		i++;
	}
	free(map->map_copy);
	return (1);
}

int	check_exit_and_collectibles(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map_copy[y][x] == 'E' || map->map_copy[y][x] == 'C'
				|| map->map_copy[y][x] == 'P')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	flood_fill(t_map *map, size_t x, size_t y)
{
	// il faut que x et y sois dans la map
	if (x < map->width && y < map->height)
	{
		if (map->map_copy[y][x] == '1' || map->map_copy[y][x] == 'M')
			return ;
		map->map_copy[y][x] = 'M'; // remplacé tout par M
		flood_fill(map, x, y - 1);
		flood_fill(map, x, y + 1);
		flood_fill(map, x - 1, y);
		flood_fill(map, x + 1, y);
	}
}
// ordre = haut, bas, gauche, droite
void	flood_fill_without_exit(t_map *map, size_t x, size_t y)
{
	// il faut que x et y sois dans la map
	if (x < map->width && y < map->height)
	{
		if (map->map_copy[y][x] == '1' || map->map_copy[y][x] == 'V')
			return ;
		map->map_copy[y][x] = 'V'; // si la case n'as pas encore était visited, on met un V
		flood_fill_without_exit(map, x, y - 1);
		flood_fill_without_exit(map, x, y + 1);
		flood_fill_without_exit(map, x - 1, y);
		flood_fill_without_exit(map, x + 1, y);
	}
}