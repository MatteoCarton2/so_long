/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:09:40 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/08 23:10:32 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	clear_gnl_buffer(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
		free(line);
}

void	free_resources(t_game *game)
{
	size_t	i;

	i = 0;
	if (game && game->map && game->map->map)
	{
		while (i < game->map->height)
		{
			if (game->map->map[i])
				free(game->map->map[i]);
			i++;
		}
		free(game->map->map);
	}
}
