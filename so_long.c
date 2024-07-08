/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:02:40 by lhopp             #+#    #+#             */
/*   Updated: 2024/07/08 12:23:12 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_map_memory(t_game *game)
{
	int	i;

	game->map = (char **)malloc(sizeof(char *) * game->map_height);
	if (!game->map)
	{
		ft_printf("Failed to allocate memory for game->map\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < game->map_height)
	{
		game->map[i] = (char *)malloc(sizeof(char) * game->map_width);
		if (!game->map[i])
		{
			ft_printf("Failed to allocate memory for game->map[%d]\n", i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	init_map(t_game *game)
{
	int	temp_tile_width;
	int	temp_tile_height;

	validate_and_calculate_map_size(game);
	temp_tile_width = game->window.width / game->map_width;
	temp_tile_height = game->window.height / game->map_height;
	if (temp_tile_width < temp_tile_height)
		game->tile_size = temp_tile_width;
	else
		game->tile_size = temp_tile_height;
	update_drawable_image(game);
	update_portal_images(game);
	allocate_map_memory(game);
	fill_map(game);
	check_map(game);
}

void	set_game_attributes(t_game *game)
{
	game->tile_size = 32;
	game->num_coins = 0;
	game->coins = NULL;
	game->spikes = NULL;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->steps = 0;
	game->player.x = -1;
	game->player.y = -1;
	game->exit.x = -1;
	game->exit.y = -1;
	game->file = NULL;
}

void	init(t_game *game, char *map_path)
{
	set_game_attributes(game);
	load_and_check_images(game);
	init_portal_images(game);
	game->file = open_file(game, map_path);
	init_map(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	game.window.mlx = mlx_init();
	game.window.win = NULL;
	game.window.width = 1920;
	game.window.height = 1080;
	init(&game, argv[1]);
	game.window.width = game.map_width * game.tile_size;
	game.window.height = game.map_height * game.tile_size;
	game.window.win = mlx_new_window(game.window.mlx, game.window.width,
			game.window.height, "so_long");
	draw_map(&game);
	mlx_key_hook(game.window.win, &handle_key, &game);
	mlx_loop_hook(game.window.mlx, &animate, &game);
	mlx_hook(game.window.win, DESTROY_NOTIFY, 0, &mlx_loop_end,
		game.window.mlx);
	mlx_loop(game.window.mlx);
	close_game(&game);
	return (0);
}
