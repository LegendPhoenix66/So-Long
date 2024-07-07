/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:36:38 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/13 14:09:06 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_coin_list(t_game *game, t_list **tmp)
{
	t_list		*prev;
	t_list		*next_temp;

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
			game->spikes_on.drawable_img, x * game->tile_size,
			y * game->tile_size);
	}
	else
	{
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->spikes_off.drawable_img, x * game->tile_size,
			y * game->tile_size);
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

void	check_player_interaction(t_game *game, int old_x, int old_y)
{
	t_list		*tmp;

	tmp = game->coins;
	while (tmp)
	{
		check_coins_interaction(game, &tmp);
	}
	tmp = game->spikes;
	while (tmp)
	{
		check_spikes_interaction(game, &tmp, old_x, old_y);
	}
	if (game->player.x == game->exit.x && game->player.y == game->exit.y
		&& game->num_coins == 0)
	{
		ft_printf("You win!\n");
		mlx_loop_end(game->window.mlx);
	}
}

void	update_seps(t_game *game)
{
	char	*steps;
	char	*temp;

	steps = ft_itoa(game->steps);
	temp = ft_strjoin("Steps: ", steps);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->wall.drawable_img, 0, 0);
	mlx_string_put(game->window.mlx, game->window.win,
		50, 50, 0x00FFFFFF, temp);
	free(temp);
	free(steps);
}

void	refresh_player_position(int *x, int *y, t_game *game, int direction)
{
	*x = game->player.x;
	*y = game->player.y;
	if (direction == MOVE_UP)
		(*y)--;
	else if (direction == MOVE_DOWN)
		(*y)++;
	else if (direction == MOVE_LEFT)
		(*x)--;
	else if (direction == MOVE_RIGHT)
		(*x)++;
}

void	update_images(t_game *game, int new_x, int new_y)
{
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->background.drawable_img, game->player.x * game->tile_size,
		game->player.y * game->tile_size);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->player_img.drawable_img, new_x * game->tile_size, new_y
		* game->tile_size);
}

void	move_player(t_game *game, int direction)
{
	int	new_x;
	int	new_y;
	int	old_x;
	int	old_y;

	old_x = game->player.x;
	old_y = game->player.y;
	refresh_player_position(&new_x, &new_y, game, direction);
	if (game->map[new_y][new_x] == '1')
		return ;
	update_images(game, new_x, new_y);
	game->player.x = new_x;
	game->player.y = new_y;
	game->steps++;
	update_seps(game);
	check_player_interaction(game, old_x, old_y);
}
