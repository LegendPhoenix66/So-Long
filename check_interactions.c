/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_interactions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:12:38 by lhopp             #+#    #+#             */
/*   Updated: 2024/07/08 12:14:39 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_coin_list(t_game *game, t_list **tmp)
{
	t_list	*prev;
	t_list	*next_temp;

	next_temp = (*tmp)->next;
	if (*tmp == game->coins)
		game->coins = next_temp;
	else
	{
		prev = game->coins;
		while (prev->next != *tmp)
			prev = prev->next;
		prev->next = next_temp;
	}
	ft_lstdelone(*tmp, free);
	*tmp = next_temp;
}

void	handle_zero_coins(t_game *game)
{
	if (game->num_coins == 0)
	{
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->exit_img.drawable_img, game->exit.x * game->tile_size,
			game->exit.y * game->tile_size);
	}
}

void	check_coins_interaction(t_game *game, t_list **tmp)
{
	t_object	*coin;

	coin = (t_object *)(*tmp)->content;
	if (coin->x != game->player.x || coin->y != game->player.y)
	{
		*tmp = (*tmp)->next;
		return ;
	}
	update_coin_list(game, tmp);
	game->num_coins--;
	handle_zero_coins(game);
}

void	display_spike_state(t_game *game, t_spikes *spike, int x, int y)
{
	if (spike->state == 0)
	{
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->spikes_on.drawable_img, x * game->tile_size, y
			* game->tile_size);
	}
	else
	{
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->spikes_off.drawable_img, x * game->tile_size, y
			* game->tile_size);
	}
}

void	check_spikes_interaction(t_game *game, t_list **tmp, int old_x,
		int old_y)
{
	t_spikes	*spike;

	spike = (t_spikes *)(*tmp)->content;
	if (spike->x == game->player.x && spike->y == game->player.y
		&& spike->state == 0)
	{
		ft_printf("You lose!\n");
		mlx_loop_end(game->window.mlx);
	}
	if (spike->x != old_x || spike->y != old_y)
	{
		*tmp = (*tmp)->next;
		return ;
	}
	display_spike_state(game, spike, old_x, old_y);
	*tmp = (*tmp)->next;
}
