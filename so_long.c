/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:02:40 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/12 16:38:28 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map(t_game *game)
{
	int	i;
	int	temp_width;
	int	temp_height;

	calculate_map_size(game);
	// calculate tile_size based on window size and map size
	temp_width = game->window.width / game->map_width;
	temp_height = game->window.height / game->map_height;
	if (temp_width < temp_height)
		game->tile_size = temp_width;
	else
		game->tile_size = temp_height;
	// resize images based on tile_size
	update_drawable_image(game);
	// Allocate memory for the 2D array
	game->map = (char **)malloc(sizeof(char *) * game->map_height);
	if (!game->map)
	{
		ft_printf("Failed to allocate memory for game->map\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < game->map_height; i++)
	{
		game->map[i] = (char *)malloc(sizeof(char) * game->map_width);
		if (!game->map[i])
		{
			ft_printf("Failed to allocate memory for game->map[%d]\n", i);
			exit(EXIT_FAILURE);
		}
	}
	fill_map(game);
	check_map(game);
}

void	init(t_game *game, char *map_path)
{
	game->tile_size = 32;
	game->num_coins = 0;
	game->coins = NULL;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->steps = 0;
	game->player.x = -1;
	game->player.y = -1;
	game->exit.x = -1;
	game->exit.y = -1;
	game->file = NULL;
	game->coin_img = load_image(game->window.mlx, "resources/collectable.xpm",
			game->tile_size);
	game->background = load_image(game->window.mlx, "resources/grass.xpm",
			game->tile_size);
	game->wall = load_image(game->window.mlx, "resources/wall.xpm",
			game->tile_size);
	game->player_img = load_image(game->window.mlx, "resources/player.xpm",
			game->tile_size);
	game->exit_img = load_image(game->window.mlx, "resources/exit.xpm",
			game->tile_size);
	if (!game->coin_img.img || !game->background.img || !game->wall.img
		|| !game->player_img.img || !game->exit_img.img)
	{
		ft_printf("Failed to load images\n");
		exit(EXIT_FAILURE);
	}
	game->file = open_file(game, map_path);
	init_map(game);
}

#include <time.h>

int animate(t_game *game)
{
    static struct timespec last_time_portal, last_time_patrol;
    static int initialized = 0;
    struct timespec current_time;
    long long elapsed_portal, elapsed_patrol;
    static int i = 0, j = 0;

    // Get the current time
    clock_gettime(CLOCK_MONOTONIC, &current_time);

    if (!initialized) {
        // This is the first frame, so there's no previous frame time to compare with
        last_time_portal = current_time;
		last_time_patrol = current_time;
        initialized = 1;
    } else {
        // Calculate elapsed time in milliseconds
        elapsed_portal = (current_time.tv_sec - last_time_portal.tv_sec) * 1000 + (current_time.tv_nsec - last_time_portal.tv_nsec) / 1000000;
		elapsed_patrol = (current_time.tv_sec - last_time_patrol.tv_sec) * 1000 + (current_time.tv_nsec - last_time_patrol.tv_nsec) / 1000000;

        if (elapsed_portal >= 150) {
            // More than 150 ms have passed since the last frame, so render the next frame
            ft_printf("i: %d\n", i);
            i++;

            // Update the time of the last frame
            last_time_portal = current_time;
        }

        if (elapsed_patrol >= 500) {
            // More than 500 ms have passed since the last frame, so render the next frame
            ft_printf("j: %d\n", j);
            j++;

            // Update the time of the last frame
            last_time_patrol = current_time;
        }
    }
	game = game;
    return (0);
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
