/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:02:40 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/23 12:08:39 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define DESTROY_NOTIFY 17

void init(t_game *game, char *map_path)
{
	int size;

	size = 256;
	char *map = open_file(map_path);
	game->background = load_image(game->window.mlx, "grass.xpm", size, size);
	game->wall = load_image(game->window.mlx, "wall.xpm", size, size);
	game->player.image = load_image(game->window.mlx, "player.xpm", size, size);
	game->exit.image = load_image(game->window.mlx, "exit.xpm", size, size);
	game->coin.image = load_image(game->window.mlx, "collectable.xpm", size, size);


	mlx_put_image_to_window(game->window.mlx, game->window.win, game->background.drawable_img, 0 * size, 0);
	mlx_put_image_to_window(game->window.mlx, game->window.win, game->wall.drawable_img, 1 * size, 0);
	mlx_put_image_to_window(game->window.mlx, game->window.win, game->player.image.drawable_img,  2 * size, 0);
	mlx_put_image_to_window(game->window.mlx, game->window.win, game->exit.image.drawable_img, 3 * size, 0);
	mlx_put_image_to_window(game->window.mlx, game->window.win, game->coin.image.drawable_img, 4 * size, 0);
	free(map);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	game.window.mlx = mlx_init();
	game.window.win = mlx_new_window(game.window.mlx, 1920, 1080, "so_long");
	init(&game, argv[1]);
	mlx_key_hook(game.window.win, handle_key, &game);
	mlx_mouse_hook(game.window.win, handle_mouse, &game);
	mlx_hook(game.window.win, DESTROY_NOTIFY, 0, &mlx_loop_end, game.window.mlx);
	mlx_loop(game.window.mlx);
	close_game(&game);
	return (0);
}