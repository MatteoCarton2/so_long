/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:13:09 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/08 22:56:18 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;

	if (argc != 2)
		handle_error("Wrong number of arguments");
	if (validate_map(argv[1], &map) == 0)
		exit(EXIT_FAILURE);
	if (check_path(&map) == 0)
		handle_error("No valid path found");
	if (init_game(&game, &map) == 0)
		handle_error("Failed to initialize game");
	return (0);
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
