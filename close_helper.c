/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:55:30 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/12 16:38:28 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_image(t_game *game, t_image *image)
{
	if (image->img)
		mlx_destroy_image(game->window.mlx, image->img);
	if (image->drawable_img)
		mlx_destroy_image(game->window.mlx, image->drawable_img);
}

void	close_game(t_game *game)
{
	destroy_image(game, &game->background);
	destroy_image(game, &game->wall);
	destroy_image(game, &game->player_img);
	destroy_image(game, &game->exit_img);
	destroy_image(game, &game->coin_img);
	ft_lstclear(&game->coins, free);
	if (game->map != NULL)
	{
		for (int i = 0; i < game->map_height; i++)
		{
			if (game->map[i] != NULL)
			{
				free(game->map[i]);
			}
		}
		free(game->map);
	}
    if (game->file) {
        free(game->file);
    }
	if (game->window.win)
		mlx_destroy_window(game->window.mlx, game->window.win);
	if (game->window.mlx) {
		mlx_destroy_display(game->window.mlx);
		free(game->window.mlx);
	}
}
