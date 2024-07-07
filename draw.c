/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:03:09 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/27 15:13:19 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_image(t_game *game, t_image image, int x, int y)
{
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		image.drawable_img, x * game->tile_size, y * game->tile_size);
}

void	draw_player(t_game *game)
{
	draw_image(game, *game->player.image, game->player.x, game->player.y);
	if (game->num_coins == 0)
		draw_image(game, *game->exit.image, game->exit.x, game->exit.y);
}

void	draw_coins(t_game *game)
{
	t_list		*tmp;
	t_object	*coin;

	tmp = game->coins;
	while (tmp)
	{
		coin = (t_object *)tmp->content;
		if (coin == NULL || coin->image == NULL
			|| coin->image->drawable_img == NULL)
		{
			ft_printf("Coin or its image is not initialized.\n");
			return ;
		}
		draw_image(game, *coin->image, coin->x, coin->y);
		tmp = tmp->next;
	}
}

void	draw_spikes(t_game *game)
{
	t_list		*tmp;
	t_spikes	*spikes;
	t_image		*current_spikes_image;

	tmp = game->spikes;
	while (tmp)
	{
		spikes = (t_spikes *)tmp->content;
		if (spikes == NULL)
		{
			ft_printf("spikes are not initialized.\n");
			return ;
		}
		if (spikes->state == 0)
			current_spikes_image = spikes->image_off;
		else
			current_spikes_image = spikes->image_on;
		draw_image(game, *current_spikes_image, spikes->x, spikes->y);
		tmp = tmp->next;
	}
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	if (game->tile_size != game->coin_img.width
		|| game->tile_size != game->coin_img.height)
	{
		update_drawable_image(game);
	}
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				draw_image(game, (game->wall), x, y);
			else if (game->map[y][x] == '0')
				draw_image(game, (game->background), x, y);
			x++;
		}
		y++;
	}
	draw_player(game);
	draw_coins(game);
	draw_spikes(game);
}
