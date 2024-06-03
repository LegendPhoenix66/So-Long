/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:02:40 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/28 11:56:19 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map(t_game *game, char *file)
{
	int			i;

	calculate_map_size(game, file);
	// calculate tile_size based on window size and map size
	int temp_width = game->window.width / game->map_width;
	int temp_height = game->window.height / game->map_height;
	if (temp_width < temp_height)
		game->tile_size = temp_width;
	else
		game->tile_size = temp_height;
	// resize images based on tile_size
    update_drawable_image(game);

	// Allocate memory for the 2D array
	game->map = (char **) malloc(sizeof(char *) * game->map_height);
	if (!game->map) {
		ft_printf("Failed to allocate memory for game->map\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < game->map_height; i++) {
		game->map[i] = (char *) malloc(sizeof(char) * game->map_width);
		if (!game->map[i]) {
			ft_printf("Failed to allocate memory for game->map[%d]\n", i);
			exit(EXIT_FAILURE);
		}
	}
	fill_map(game, file);
	check_map(game);
}

void	init(t_game *game, char *map_path)
{
	char	*file;

	game->tile_size = 32;
	game->num_coins = 0;
	game->coins = NULL;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;
    game->steps = 0;

	game->coin_img = load_image(game->window.mlx, "collectable.xpm", game->tile_size);
	game->background = load_image(game->window.mlx, "grass.xpm", game->tile_size);
	game->wall = load_image(game->window.mlx, "wall.xpm", game->tile_size);
	game->player_img = load_image(game->window.mlx, "player.xpm", game->tile_size);
	game->exit_img = load_image(game->window.mlx, "exit.xpm", game->tile_size);

	if (!game->coin_img.img || !game->background.img || !game->wall.img || !game->player_img.img || !game->exit_img.img)
	{
		ft_printf("Failed to load images\n");
		exit(EXIT_FAILURE);
	}

    file = open_file(map_path);
    init_map(game, file);
    free(file);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	game.window.mlx = mlx_init();

	game.window.width = 1920;
	game.window.height = 1080;
    init(&game, argv[1]);
    game.window.width = game.map_width * game.tile_size;
    game.window.height = game.map_height * game.tile_size;
	game.window.win = mlx_new_window(game.window.mlx, game.window.width,
		game.window.height, "so_long");
	draw_map(&game);
	mlx_key_hook(game.window.win, &handle_key, &game);
	mlx_mouse_hook(game.window.win, &handle_mouse, &game);
	mlx_hook(game.window.win, DESTROY_NOTIFY, 0, &mlx_loop_end,
		game.window.mlx);
	mlx_loop(game.window.mlx);
	close_game(&game);
	return (0);
}
