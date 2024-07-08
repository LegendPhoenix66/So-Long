/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:36:38 by lhopp             #+#    #+#             */
/*   Updated: 2024/07/08 12:14:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_player_interaction(t_game *game, int old_x, int old_y)
{
	t_list	*tmp;

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
	mlx_string_put(game->window.mlx, game->window.win, 50, 50, 0x00FFFFFF,
		temp);
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
