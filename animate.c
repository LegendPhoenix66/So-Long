/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:57 by lhopp             #+#    #+#             */
/*   Updated: 2024/07/08 12:19:10 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

long long	calculate_elapsed_time(struct timespec current_time,
		struct timespec last_time_portal)
{
	return ((current_time.tv_sec - last_time_portal.tv_sec) * 1000
		+ (current_time.tv_nsec - last_time_portal.tv_nsec) / 1000000);
}

void	handle_spike_state(t_game *game, t_spikes *spike)
{
	t_image	*image;

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
		mlx_put_image_to_window(game->window.mlx, game->window.win, image,
			spike->x * game->tile_size, spike->y * game->tile_size);
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
			image->drawable_img, game->exit.x * game->tile_size, game->exit.y
			* game->tile_size);
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
