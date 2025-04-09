/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:27:35 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/09 21:22:17 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	validate_map(char *filename, t_map *map)
{
	map->p_counter = 0;
	map->e_counter = 0;
	map->c_counter = 0;
	if (!check_extension(filename))
		handle_error("Invalid file extension");
	if (!check_rectangle(filename, map))
		handle_error("Map must be rectangular");
	if (!store_map(filename, map))
		handle_error("Failed to store map in memory");
	if (!check_walls(map))
	{
		free_map_resources(map, map->height, NULL, -1);
		handle_error("Map must be surrounded by walls");
	}
	if (!count_elements(filename, map))
	{
		free_map_resources(map, map->height, NULL, -1);
		handle_error("Invalid map elements configuration");
	}
	return (1);
}

// +1 pour le \0
static int	store_map_line(char *line, t_map *map, size_t i)
{
	size_t	j;

	j = 0;
	map->map[i] = malloc(sizeof(char) * map->width + 1);
	if (!map->map[i])
		return (0);
	map->map_copy[i] = malloc(sizeof(char) * map->width + 1);
	if (!map->map_copy[i])
	{
		free(map->map[i]);
		return (0);
	}
	while (line[j] != '\0')
	{
		map->map[i][j] = line[j];
		map->map_copy[i][j] = line[j];
		j++;
	}
	return (1);
}

static int	allocate_map_memory(t_map *map, char *line, int fd)
{
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		return (free(line), close(fd), 0);
	map->map_copy = malloc(sizeof(char *) * map->height);
	if (!map->map_copy)
	{
		free(map->map);
		return (free(line), close(fd), 0);
	}
	return (1);
}

int	store_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	size_t	i;

	fd = open_and_get_line(filename, &line);
	if (fd == -1)
		return (0);
	if (!allocate_map_memory(map, line, fd))
		return (0);
	i = 0;
	while (i < map->height)
	{
		if (!store_map_line(line, map, i))
		{
			free_map_resources(map, i, line, fd);
			return (0);
		}
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	count_elements(char *filename, t_map *map)
{
	char	*line;
	int		fd;

	fd = open_and_get_line(filename, &line);
	if (fd == -1)
		return (0);
	while (line != NULL)
	{
		if (count_line_elements(line, map) == 0)
			return (free(line), clear_gnl_buffer(fd), close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map->p_counter != 1 || map->e_counter != 1 || map->c_counter < 1)
		return (0);
	map->collectibles = map->c_counter;
	return (1);
}
