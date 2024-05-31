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
#define DESTROY_NOTIFY 17

void	init_map(t_game *game, char *file)
{
	int			i;

	calculate_map_size(game, file);
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
}

void	draw_map(t_game *game)
{
	int x, y;
	for (y = 0; y < game->map_height; y++)
	{
		for (x = 0; x < game->map_width; x++)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->window.mlx, game->window.win,
					game->wall.drawable_img, x * game->tile_size, y
					* game->tile_size);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->window.mlx, game->window.win,
					game->background.drawable_img, x * game->tile_size, y
					* game->tile_size);
		}
	}
	mlx_put_image_to_window(game->window.mlx, game->window.win,
    game->player.image->drawable_img, game->player.x * game->tile_size,
		game->player.y * game->tile_size);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->exit.image->drawable_img, game->exit.x * game->tile_size,
		game->exit.y * game->tile_size);

	t_list *tmp = game->coins;
	while (tmp) {
		t_object *coin = (t_object *) tmp->content;
		if (coin == NULL) {
			ft_printf("coin is not initialized.\n");
			return;
		}
		if (game->window.mlx == NULL) {
			ft_printf("game->window.mlx is not initialized.\n");
			return;
		}
		if (game->window.win == NULL) {
			ft_printf("game->window.win is not initialized.\n");
			return;
		}
		if (coin->image == NULL) {
			ft_printf("coin->image is not initialized.\n");
			return;
		}
		if (coin->image->drawable_img == NULL) {
			ft_printf("coin->image->drawable_img is not initialized.\n");
			return;
		}
		mlx_put_image_to_window(game->window.mlx, game->window.win,
								coin->image->drawable_img, coin->x * game->tile_size,
								coin->y * game->tile_size);
		tmp = tmp->next;
	}
}

void print_game(t_game game){
	ft_printf("game->window: %p\n", &game.window);
	ft_printf("game->coin_img: %p\n", &game.coin_img);
	ft_printf("game->player_img: %p\n", &game.player_img);
	ft_printf("game->exit_img: %p\n", &game.exit_img);
	ft_printf("game->background: %p\n", &game.background);
	ft_printf("game->wall: %p\n", &game.wall);
	ft_printf("game->player: %p\n", &game.player);
	ft_printf("game->exit: %p\n", &game.exit);
	ft_printf("game->coins: %p\n", game.coins);
	ft_printf("game->num_coins: %d\n", game.num_coins);
	ft_printf("game->map: %p\n", game.map);
	ft_printf("game->map_width: %d\n", game.map_width);
	ft_printf("game->map_height: %d\n", game.map_height);
	ft_printf("game->tile_size: %d\n", game.tile_size);
}

void	init(t_game *game, char *map_path)
{
	char	*file;

	game->tile_size = 128;
	game->num_coins = 0;
	game->coins = NULL;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;

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
	draw_map(game);
//	print_game(*game);
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
	mlx_hook(game.window.win, DESTROY_NOTIFY, 0, &mlx_loop_end,
		game.window.mlx);
	mlx_loop(game.window.mlx);
	close_game(&game);
	return (0);
}
