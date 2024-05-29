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
	int			x;
	int 		y;
	char		c;
	t_object	coin;

	game->coins = NULL;
	calculate_map_size(game, file);
	// Allocate memory for the 2D array
	game->map = (char **)malloc(sizeof(char *) * game->map_height);
	for (i = 0; i < game->map_height; i++)
	{
		game->map[i] = (char *)malloc(sizeof(char) * game->map_width);
	}
	// Now, fill the 2D array with the map data
	x = 0, y = 0;
	i = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '\n')
		{
			y++;
			x = 0;
		}
		else
		{
			c = file[i];
			if (c == '1' || c == '0')
			{
				game->map[y][x] = c;
			}
			else if (c == 'P')
			{
				game->player.x = x;
				game->player.y = y;
                game->player.image = &game->player_img;
				game->map[y][x] = '0';
			}
			else if (c == 'E')
			{
				game->exit.x = x;
				game->exit.y = y;
                game->exit.image = &game->exit_img;
				game->map[y][x] = '0';
			}
			else if (c == 'C')
			{
				game->num_coins++;
				coin.x = x;
				coin.y = y;
				coin.image = &game->coin_img;
//                ft_printf("\n%p\n", game->coin.image.drawable_img);
//                ft_printf("\n%p\n", coin.image.drawable_img);
				ft_lstadd_front(&game->coins, ft_lstnew(&coin));
				game->map[y][x] = '0';
			}
			x++;
		}
		i++;
	}
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
	while (tmp)
	{
        t_object *coin = (t_object *)tmp->content;
		coin = coin;
//			mlx_put_image_to_window(game->window.mlx, game->window.win,
//			coin->image->drawable_img, coin->x * game->tile_size,
//			coin->y * game->tile_size);
        ft_printf("game->coin_img: %p\n", game->coin_img);
        ft_printf("coin->image: %p\n", coin->image);
//        ft_printf("coin->x: %d\n", coin->x);
//        ft_printf("coin->y: %d\n", coin->y);
		tmp = tmp->next;
	}
}

void	init(t_game *game, char *map_path)
{
	char	*file;

	game->tile_size = 128;

    game->coin_img = load_image(game->window.mlx, "collectable.xpm",
                                game->tile_size, game->tile_size);
	game->background = load_image(game->window.mlx, "grass.xpm",
			game->tile_size, game->tile_size);
	game->wall = load_image(game->window.mlx, "wall.xpm", game->tile_size,
			game->tile_size);
	game->player_img = load_image(game->window.mlx, "player.xpm",
			game->tile_size, game->tile_size);
	game->exit_img = load_image(game->window.mlx, "exit.xpm", game->tile_size,
			game->tile_size);

    ft_printf("game->coin_img: %p\n", game->coin_img);
    ft_printf("game->player_img: %p\n", game->player_img);

    file = open_file(map_path);
    init_map(game, file);
    free(file);
	draw_map(game);
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
