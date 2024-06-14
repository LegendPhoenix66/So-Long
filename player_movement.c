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

void	check_tile(t_game *game, int x, int y)
{
	t_list		*tmp;
	t_object	*coin;
	t_list		*prev;
	t_list		*next_temp;

	// check for coin
	tmp = game->coins;
	while (tmp)
	{
		coin = (t_object *)tmp->content;
		if (coin->x == x && coin->y == y)
		{
			next_temp = tmp->next;
			// remove coin from list
			if (tmp == game->coins)
			{
				game->coins = next_temp;
			}
			else
			{
				prev = game->coins;
				while (prev->next != tmp)
					prev = prev->next;
				prev->next = next_temp;
			}
			ft_lstdelone(tmp, free);
			tmp = next_temp;
			game->num_coins--;
			// if no coins left, draw exit
			if (game->num_coins == 0)
			{
				mlx_put_image_to_window(game->window.mlx, game->window.win,
					game->exit_img.drawable_img, game->exit.x * game->tile_size,
					game->exit.y * game->tile_size);
			}
		}
		else
		{
			tmp = tmp->next;
		}
	}
	// check for exit
	if (game->player.x == game->exit.x && game->player.y == game->exit.y
		&& game->num_coins == 0)
	{
		ft_printf("You win!\n");
		mlx_loop_end(game->window.mlx);
	}
}

void update_seps(t_game *game)
{
	char *steps = ft_itoa(game->steps);
	char *temp = ft_strjoin("Steps: ", steps);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
							game->wall.drawable_img, 0, 0);
	mlx_string_put(game->window.mlx, game->window.win, 50, 50, 0x00FFFFFF, temp);
	free(temp);
	free(steps);
}

void	move_player(t_game *game, int direction)
{
	int	new_x;
	int	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (direction == MOVE_UP)
		new_y--;
	else if (direction == MOVE_DOWN)
		new_y++;
	else if (direction == MOVE_LEFT)
		new_x--;
	else if (direction == MOVE_RIGHT)
		new_x++;
	if (game->map[new_y][new_x] == '1')
		return ;
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->background.drawable_img, game->player.x * game->tile_size,
		game->player.y * game->tile_size);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->player_img.drawable_img, new_x * game->tile_size, new_y
		* game->tile_size);
	game->player.x = new_x;
	game->player.y = new_y;
	game->steps++;
	update_seps(game);
	check_tile(game, new_x, new_y);
}
