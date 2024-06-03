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

void calculate_map_size(t_game *game, char *file)
{
	int i;
    int temp_width = 0;

	game->map_width = 0;
	game->map_height = 1;
	i = 0;
	// First, count the width and height of the map
	while (file[i] != '\0') {
		if (file[i] == '\n') {
			game->map_height++;
            if (game->map_width != 0 && temp_width != game->map_width) {
                ft_printf("Map is not rectangular.\n");
                free(file);
                close_game(game);
                exit(EXIT_FAILURE);
            }
            game->map_width = temp_width;
			temp_width = 0;
		} else
			temp_width++;
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

void	draw_map(t_game *game)
{
    if (game->tile_size != game->coin_img.width || game->tile_size != game->coin_img.height) {
        update_drawable_image(game);
    }
	int x, y;
    for (y = 0; y < game->map_height; y++) {
        for (x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->window.mlx, game->window.win, game->wall.drawable_img, x * game->tile_size, y * game->tile_size);
            else if (game->map[y][x] == '0')
                mlx_put_image_to_window(game->window.mlx, game->window.win, game->background.drawable_img, x * game->tile_size, y * game->tile_size);
        }
    }
	mlx_put_image_to_window(game->window.mlx, game->window.win,
							game->player.image->drawable_img, game->player.x * game->tile_size,
							game->player.y * game->tile_size);
    if (game->num_coins == 0)
	    mlx_put_image_to_window(game->window.mlx, game->window.win,
							game->exit.image->drawable_img, game->exit.x * game->tile_size,
							game->exit.y * game->tile_size);

	t_list *tmp = game->coins;
	while (tmp) {
		t_object *coin = (t_object *) tmp->content;
		if (coin == NULL) {
			ft_printf("coin is not initialized.\n");
			return;
		}
		if (game->window.mlx == NULL) {
			ft_printf("game->window.mlx is not initialized.\n");
			return;
		}
		if (game->window.win == NULL) {
			ft_printf("game->window.win is not initialized.\n");
			return;
		}
		if (coin->image == NULL) {
			ft_printf("coin->image is not initialized.\n");
			return;
		}
		if (coin->image->drawable_img == NULL) {
			ft_printf("coin->image->drawable_img is not initialized.\n");
			return;
		}
		mlx_put_image_to_window(game->window.mlx, game->window.win,
								coin->image->drawable_img, coin->x * game->tile_size,
								coin->y * game->tile_size);
		tmp = tmp->next;
	}
}

char **copy_map(t_game *game) {
    char **copy = (char **) malloc(sizeof(char *) * game->map_height);
    for (int i = 0; i < game->map_height; i++) {
        copy[i] = (char *) malloc(sizeof(char) * game->map_width);
        for (int j = 0; j < game->map_width; j++) {
            copy[i][j] = game->map[i][j];
        }
    }
    return copy;
}

void free_map(char **map, t_game *game)
{
	for (int i = 0; i < game->map_height; i++) {
		free(map[i]);
	}
	free(map);
}

int can_reach(t_game *game, int x1, int y1, int x2, int y2, char **map_copy)
{
	if (x1 < 0 || x1 >= game->map_width || y1 < 0 || y1 >= game->map_height) {
		return 0;
	}
	if (map_copy[y1][x1] == '1') {
		return 0;
	}
	if (x1 == x2 && y1 == y2)
		return 1;
	map_copy[y1][x1] = '1';
	if (can_reach(game, x1 + 1, y1, x2, y2, map_copy))
		return 1;
	if (can_reach(game, x1 - 1, y1, x2, y2, map_copy))
		return 1;
	if (can_reach(game, x1, y1 + 1, x2, y2, map_copy))
		return 1;
	if (can_reach(game, x1, y1 - 1, x2, y2, map_copy))
		return 1;
	return 0;
}

void check_map(t_game *game)
{
	if (game->player.x == -1 || game->player.y == -1) {
		ft_printf("Player not found in the map.\n");
		exit(EXIT_FAILURE);
	}
	if (game->exit.x == -1 || game->exit.y == -1) {
		ft_printf("Exit not found in the map.\n");
		exit(EXIT_FAILURE);
	}
	if (game->num_coins == 0) {
		ft_printf("No coins found in the map.\n");
		exit(EXIT_FAILURE);
	}
	// Check if the map is surrounded by walls
	for (int x = 0; x < game->map_width; x++) {
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1') {
			ft_printf("Map is not surrounded by walls.\n");
			exit(EXIT_FAILURE);
		}
	}
	// Check if the player can reach every coin and the exit
	char **map_copy = copy_map(game);
	if (!can_reach(game, game->player.x, game->player.y, game->exit.x, game->exit.y, map_copy)) {
		ft_printf("Player cannot reach the exit.\n");
		exit(EXIT_FAILURE);
	}
	free_map(map_copy, game);
	t_list *tmp = game->coins;
	while (tmp) {
		t_object *coin = (t_object *) tmp->content;
		if (coin == NULL) {
			ft_printf("coin is not initialized.\n");
			exit(EXIT_FAILURE);
		}
		map_copy = copy_map(game);
		if (!can_reach(game, game->player.x, game->player.y, coin->x, coin->y, map_copy)) {
			ft_printf("Player cannot reach a coin.\n");
			ft_printf("coin at x: %d, y: %d\n", coin->x, coin->y);
			exit(EXIT_FAILURE);
		}
		free_map(map_copy, game);
		tmp = tmp->next;
	}
}

