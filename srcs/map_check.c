/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:16:17 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/08 21:15:22 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_extension(char *filename)
{
	int	length;

	length = ft_strlen(filename);
	if (length < 4)
		return (0);
	if (ft_strncmp(filename + (length - 4), ".ber", 4) == 0)
		return (1);
	return (0);
}

int	check_rectangle(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open_and_get_line(filename, &line);
	if (fd == -1)
		return (0);
	map->width = (ft_strlen(line) - 1);
	map->height = 1;
	free(line);
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		if (len != map->width)
			return (free(line), close(fd), 0);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

// Vérifier 1ère et dernière ligne puis 1ère et dernière colonne
int	check_walls(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->width)
	{
		if (map->map[0][i] != '1' || map->map[map->height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	free_map_resources(t_map *map, size_t current_row, char *line, int fd)
{
	size_t	i;

	i = 0;
	while (i < current_row)
	{
		free(map->map[i]);
		free(map->map_copy[i]);
		i++;
	}
	free(map->map);
	free(map->map_copy);
	free(line);
	close(fd);
}

int	count_line_elements(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'P')
			map->p_counter++;
		else if (line[i] == 'E')
			map->e_counter++;
		else if (line[i] == 'C')
			map->c_counter++;
		else if (line[i] != '0' && line[i] != '1' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
