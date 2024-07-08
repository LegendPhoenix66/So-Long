/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:21:56 by lhopp             #+#    #+#             */
/*   Updated: 2024/07/08 12:23:08 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
