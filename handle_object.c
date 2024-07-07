/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:36:38 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/13 14:09:06 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_player(t_game *game, int x, int y)
{
	if (game->player.x != -1 || game->player.y != -1)
	{
		ft_printf("Error\nMultiple players found in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	game->player.x = x;
	game->player.y = y;
	game->player.image = &game->player_img;
}

void	handle_exit(t_game *game, int x, int y)
{
	if (game->exit.x != -1 || game->exit.y != -1)
	{
		ft_printf("Error\nMultiple exits found in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	game->exit.x = x;
	game->exit.y = y;
	game->exit.image = &game->exit_img;
}

void	handle_coin(t_game *game, int x, int y)
{
	t_object	*coin;

	game->num_coins++;
	coin = malloc(sizeof(t_object));
	if (coin == NULL)
	{
		ft_printf("Failed to allocate memory for coin.\n");
		exit(EXIT_FAILURE);
	}
	coin->x = x;
	coin->y = y;
	coin->image = &game->coin_img;
	ft_lstadd_front(&game->coins, ft_lstnew(coin));
}

void	handle_spikes(t_game *game, int x, int y)
{
	t_spikes	*spikes;

	spikes = malloc(sizeof(t_spikes));
	if (spikes == NULL)
	{
		ft_printf("Failed to allocate memory for spikes.\n");
		exit(EXIT_FAILURE);
	}
	spikes->x = x;
	spikes->y = y;
	spikes->state = 0;
	spikes->image_on = &game->spikes_on;
	spikes->image_off = &game->spikes_off;
	ft_lstadd_front(&game->spikes, ft_lstnew(spikes));
}
