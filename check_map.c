/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:36:38 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/13 14:09:06 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_initial_conditions(t_game *game)
{
	if (game->player.x == -1 || game->player.y == -1)
		error_and_exit(game, "Player not found in the map.");
	if (game->exit.x == -1 || game->exit.y == -1)
		error_and_exit(game, "Exit not found in the map.");
	if (game->num_coins == 0)
		error_and_exit(game, "No coins found in the map.");
	check_walls(game);
}

void	check_player_can_reach_exit(t_game *game, t_position start,
									t_position target)
{
	target.x = game->exit.x;
	target.y = game->exit.y;
	if (!can_reach_target(game, start, target))
		error_and_exit(game, "Player cannot reach the exit.");
}

void	check_player_can_reach_coins(t_game *game, t_list *coins,
			t_position start, t_position target)
{
	t_object	*coin;

	while (coins)
	{
		coin = (t_object *) coins->content;
		if (coin == NULL)
			error_and_exit(game, "coin is not initialized.");
		target.x = coin->x;
		target.y = coin->y;
		if (!can_reach_target(game, start, target))
			error_and_exit(game, "Player cannot reach a coin.");
		coins = coins->next;
	}
}

void	check_map(t_game *game)
{
	t_position	start;
	t_position	target;

	check_initial_conditions(game);
	start.x = game->player.x;
	start.y = game->player.y;
	check_player_can_reach_exit(game, start, target);
	check_player_can_reach_coins(game, game->coins, start, target);
}
