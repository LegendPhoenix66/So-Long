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

void	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
			error_and_exit(game, "Map is not surrounded by walls.");
		i++;
	}
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
			error_and_exit(game, "Map is not surrounded by walls.");
		i++;
	}
}

void	check_map_uniformity_and_exit_on_failure(t_game *game, int temp_width)
{
	if (game->map_width != 0 && temp_width != game->map_width)
	{
		ft_printf("Error\nMap is not rectangular.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
}

void	check_map_last_line_and_exit_on_failure(t_game *game, int temp_width)
{
	if (temp_width != game->map_width)
	{
		ft_printf("Error\nMap is not rectangular.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
}

void	check_map_empty_and_exit_on_failure(t_game *game)
{
	if (game->map_height == 1 || game->map_width == 0)
	{
		ft_printf("Error\nMap is empty.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
}

void	validate_and_calculate_map_size(t_game *game)
{
	int	i;
	int	temp_width;

	temp_width = 0;
	game->map_width = 0;
	game->map_height = 1;
	i = 0;
	while (game->file[i] != '\0')
	{
		if (game->file[i] == '\n')
		{
			game->map_height++;
			check_map_uniformity_and_exit_on_failure(game, temp_width);
			game->map_width = temp_width;
			temp_width = 0;
		}
		else
		{
			temp_width++;
		}
		i++;
	}
	check_map_last_line_and_exit_on_failure(game, temp_width);
	check_map_empty_and_exit_on_failure(game);
}
