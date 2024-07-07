/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:03:09 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/27 15:13:19 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_drawable_image(t_game *game)
{
	mlx_destroy_image(game->window.mlx, game->coin_img.drawable_img);
	set_drawable_image(game->window.mlx, &game->coin_img, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->background.drawable_img);
	set_drawable_image(game->window.mlx, &game->background, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->wall.drawable_img);
	set_drawable_image(game->window.mlx, &game->wall, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->player_img.drawable_img);
	set_drawable_image(game->window.mlx, &game->player_img, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->exit_img.drawable_img);
	set_drawable_image(game->window.mlx, &game->exit_img, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->spikes_on.drawable_img);
	set_drawable_image(game->window.mlx, &game->spikes_on, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->spikes_off.drawable_img);
	set_drawable_image(game->window.mlx, &game->spikes_off, game->tile_size,
		game->tile_size);
}

void	update_portal_images(t_game *game)
{
	t_list	*tmp;
	int		i;
	t_list	*first;

	tmp = game->portal_images;
	i = 0;
	if (tmp != NULL)
	{
		first = tmp;
		while (tmp->next != first)
		{
			mlx_destroy_image(game->window.mlx,
				((t_image *)tmp->content)->drawable_img);
			set_drawable_image(game->window.mlx, (t_image *)tmp->content,
				game->tile_size, game->tile_size);
			tmp = tmp->next;
			i++;
		}
		mlx_destroy_image(game->window.mlx,
			((t_image *)tmp->content)->drawable_img);
		set_drawable_image(game->window.mlx, (t_image *)tmp->content,
			game->tile_size, game->tile_size);
	}
}
