/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:13:09 by mcarton           #+#    #+#             */
/*   Updated: 2025/04/09 20:30:01 by mcarton          ###   ########.fr       */
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
	{
		free_map_resources(&map, map.height, NULL, -1);
		handle_error("No valid path found");
	}
	if (init_game(&game, &map) == 0)
		handle_error("Failed to initialize game");
	return (0);
}
