/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:56:02 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/28 11:56:07 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void calculate_map_size(t_game *game, const char *file)
{
	int i;

	game->map_width = 0;
	game->map_height = 1;
	i = 0;
	// First, count the width and height of the map
	while (file[i] != '\0') {
		if (file[i] == '\n') {
			game->map_height++;
			game->map_width = 0;
		} else
			game->map_width++;
		i++;
	}
}

void handle_character(t_game *game, char c, int x, int y)
{
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height) {
		if (c == '1') {
			game->map[y][x] = '1';
		} else {
			game->map[y][x] = '0';
		}
	}
	if (c == 'P') {
		game->player.x = x;
		game->player.y = y;
		game->player.image = &game->player_img;
	} else if (c == 'E') {
		game->exit.x = x;
		game->exit.y = y;
		game->exit.image = &game->exit_img;
	} else if (c == 'C') {
		game->num_coins++;
		t_object *coin = malloc(sizeof(t_object));
		if (coin == NULL) {
			ft_printf("Failed to allocate memory for coin.\n");
			exit(EXIT_FAILURE);
		}
		coin->x = x;
		coin->y = y;
		coin->image = &game->coin_img;
		ft_lstadd_front(&game->coins, ft_lstnew(coin));
	}
}

void fill_map(t_game *game, char *file)
{
	int x = 0;
	int y = 0;

	for (int i = 0; file[i] != '\0'; i++) {
		if (file[i] == '\n') {
			y++;
			x = 0;
		} else {
			handle_character(game, file[i], x, y);
			x++;
		}
	}
}
