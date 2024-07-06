/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:02:40 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/27 12:51:38 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_map_memory(t_game *game)
{
	int	i;

	game->map = (char **) malloc(sizeof(char *) * game->map_height);
	if (!game->map)
	{
		ft_printf("Failed to allocate memory for game->map\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < game->map_height)
	{
		game->map[i] = (char *) malloc(sizeof(char) * game->map_width);
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

	calculate_map_size(game);
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

void	add_portal_image(t_game *game, char *image_path)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
	{
		ft_printf("Failed to allocate memory for portal image\n");
		exit(EXIT_FAILURE);
	}
	*image = load_image(game->window.mlx, image_path, game->tile_size);
	ft_lstadd_front(&game->portal_images, ft_lstnew(image));
}

void	init_portal_images(t_game *game)
{
	char	*image_paths[6];
	int		num_images;
	int		i;

	image_paths[0] = "resources/portal-blue-0.xpm";
	image_paths[1] = "resources/portal-blue-1.xpm";
	image_paths[2] = "resources/portal-blue-2.xpm";
	image_paths[3] = "resources/portal-blue-3.xpm";
	image_paths[4] = "resources/portal-blue-4.xpm";
	image_paths[5] = "resources/portal-blue-5.xpm";
	num_images = sizeof(image_paths) / sizeof(image_paths[0]);
	game->portal_images = NULL;
	i = 0;
	while (i < num_images)
	{
		add_portal_image(game, image_paths[i]);
		i++;
	}
	ft_lstlast(game->portal_images)->next = game->portal_images;
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

void	load_and_check_images(t_game *game)
{
	game->spikes_on = load_image(game->window.mlx, "resources/spikes-on.xpm",
			game->tile_size);
	game->spikes_off = load_image(game->window.mlx, "resources/spikes-off.xpm",
			game->tile_size);
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
}

void	init(t_game *game, char *map_path)
{
	set_game_attributes(game);
	load_and_check_images(game);
	init_portal_images(game);
	game->file = open_file(game, map_path);
	init_map(game);
}

long long	calculate_elapsed_time(struct timespec current_time,
		struct timespec last_time_portal)
{
	return ((current_time.tv_sec - last_time_portal.tv_sec) * 1000
		+ (current_time.tv_nsec - last_time_portal.tv_nsec) / 1000000);
}

void	handle_spike_state(t_game *game, t_spikes *spike)
{
	t_image		*image;

	if (spike->state == 6)
	{
		spike->state = 0;
		image = game->spikes_on.drawable_img;
		if (game->player.x == spike->x && game->player.y == spike->y)
		{
			ft_printf("You died!\n");
			mlx_loop_end(game->window.mlx);
		}
	}
	else
	{
		spike->state = spike->state + 1;
		image = game->spikes_off.drawable_img;
	}
	if (spike->state < 2)
	{
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			image, spike->x * game->tile_size, spike->y * game->tile_size);
	}
}

void	update_spikes(t_game *game, struct timespec current_time,
					struct timespec *last_time_portal)
{
	t_spikes	*spike;
	t_list		*tmp;

	tmp = game->spikes;
	while (tmp)
	{
		spike = (t_spikes *)tmp->content;
		handle_spike_state(game, spike);
		tmp = tmp->next;
	}
	*last_time_portal = current_time;
}

void	check_game_end(t_game *game)
{
	t_image	*image;

	if (game->num_coins == 0)
	{
		image = game->portal_images->content;
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			image->drawable_img, game->exit.x * game->tile_size,
			game->exit.y * game->tile_size);
		game->portal_images = game->portal_images->next;
	}
}

int	animate(t_game *game)
{
	static int				initialized = 0;
	static struct timespec	last_time_portal;
	long long				elapsed_portal;
	struct timespec			current_time;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	if (!initialized)
	{
		last_time_portal = current_time;
		initialized = 1;
	}
	else
	{
		elapsed_portal = calculate_elapsed_time(current_time, last_time_portal);
		if (elapsed_portal >= 150)
		{
			update_spikes(game, current_time, &last_time_portal);
			check_game_end(game);
		}
	}
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
