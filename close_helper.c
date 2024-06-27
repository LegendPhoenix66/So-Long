/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:55:30 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/27 15:49:07 by lhopp            ###   ########.fr       */
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

void	close_map(t_game *game)
{
	int	i;

	if (game->map != NULL)
	{
		i = 0;
		while (i < game->map_height)
		{
			if (game->map[i] != NULL)
			{
				free(game->map[i]);
			}
			i++;
		}
		free(game->map);
	}
}

void	destroy_portal_images(t_game *game)
{
	t_list	*tmp;

	tmp = game->portal_images;
	while (tmp->next != game->portal_images)
	{
		tmp = tmp->next;
	}
	tmp->next = NULL;
	tmp = game->portal_images;
	while (tmp)
	{
		destroy_image(game, (t_image *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&game->portal_images, free);
}

void	close_game(t_game *game)
{
	destroy_image(game, &game->background);
	destroy_image(game, &game->wall);
	destroy_image(game, &game->player_img);
	destroy_image(game, &game->exit_img);
	destroy_image(game, &game->coin_img);
	destroy_portal_images(game);
	ft_lstclear(&game->coins, free);
	close_map(game);
	if (game->file)
	{
		free(game->file);
	}
	if (game->window.win)
		mlx_destroy_window(game->window.mlx, game->window.win);
	if (game->window.mlx)
	{
		mlx_destroy_display(game->window.mlx);
		free(game->window.mlx);
	}
}
