/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:56:02 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/13 15:46:46 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_invalid_character(t_game *game, char c)
{
	if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C' && c != 'X')
	{
		ft_printf("Error\nInvalid character in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
}

void	handle_map_building(t_game *game, char c, int x, int y)
{
	if (c == '1')
	{
		game->map[y][x] = '1';
	}
	else
	{
		game->map[y][x] = '0';
	}
}

void	handle_character(t_game *game, char c, int x, int y)
{
	handle_invalid_character(game, c);
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
		handle_map_building(game, c, x, y);
	if (c == 'P')
		handle_player(game, x, y);
	else if (c == 'E')
		handle_exit(game, x, y);
	else if (c == 'C')
		handle_coin(game, x, y);
	else if (c == 'X')
		handle_spikes(game, x, y);
}

void	fill_map(t_game *game)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	while (game->file[i] != '\0')
	{
		if (game->file[i] == '\n')
		{
			y++;
			x = 0;
		}
		else
		{
			handle_character(game, game->file[i], x, y);
			x++;
		}
		i++;
	}
}

void	error_and_exit(t_game *game, char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	close_game(game);
	exit(EXIT_FAILURE);
}
