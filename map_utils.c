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

void	handle_player(t_game *game, int x, int y)
{
	if (game->player.x != -1 || game->player.y != -1)
	{
		ft_printf("Error\nMultiple players found in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	game->player.x = x;
	game->player.y = y;
	game->player.image = &game->player_img;
}

void	handle_exit(t_game *game, int x, int y)
{
	if (game->exit.x != -1 || game->exit.y != -1)
	{
		ft_printf("Error\nMultiple exits found in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	game->exit.x = x;
	game->exit.y = y;
	game->exit.image = &game->exit_img;
}

void	handle_coin(t_game *game, int x, int y)
{
	t_object	*coin;

	game->num_coins++;
	coin = malloc(sizeof(t_object));
	if (coin == NULL)
	{
		ft_printf("Failed to allocate memory for coin.\n");
		exit(EXIT_FAILURE);
	}
	coin->x = x;
	coin->y = y;
	coin->image = &game->coin_img;
	ft_lstadd_front(&game->coins, ft_lstnew(coin));
}

void	handle_spikes(t_game *game, int x, int y)
{
	t_spikes	*spikes;

	spikes = malloc(sizeof(t_spikes));
	if (spikes == NULL)
	{
		ft_printf("Failed to allocate memory for spikes.\n");
		exit(EXIT_FAILURE);
	}
	spikes->x = x;
	spikes->y = y;
	spikes->state = 0;
	spikes->image_on = &game->spikes_on;
	spikes->image_off = &game->spikes_off;
	ft_lstadd_front(&game->spikes, ft_lstnew(spikes));
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

void	draw_image(t_game *game, t_image image, int x, int y)
{
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		image.drawable_img, x * game->tile_size, y * game->tile_size);
}

void	draw_player(t_game *game)
{
	draw_image(game, *game->player.image, game->player.x, game->player.y);
	if (game->num_coins == 0)
		draw_image(game, *game->exit.image, game->exit.x, game->exit.y);
}

void	draw_coins(t_game *game)
{
	t_list		*tmp;
	t_object	*coin;

	tmp = game->coins;
	while (tmp)
	{
		coin = (t_object *)tmp->content;
		if (coin == NULL || coin->image == NULL
			|| coin->image->drawable_img == NULL)
		{
			ft_printf("Coin or its image is not initialized.\n");
			return ;
		}
		draw_image(game, *coin->image, coin->x, coin->y);
		tmp = tmp->next;
	}
}

void	draw_spikes(t_game *game)
{
	t_list		*tmp;
	t_spikes	*spikes;
	t_image		*current_spikes_image;

	tmp = game->spikes;
	while (tmp)
	{
		spikes = (t_spikes *)tmp->content;
		if (spikes == NULL)
		{
			ft_printf("spikes are not initialized.\n");
			return ;
		}
		if (spikes->state == 0)
			current_spikes_image = spikes->image_off;
		else
			current_spikes_image = spikes->image_on;
		draw_image(game, *current_spikes_image, spikes->x, spikes->y);
		tmp = tmp->next;
	}
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	if (game->tile_size != game->coin_img.width
		|| game->tile_size != game->coin_img.height)
	{
		update_drawable_image(game);
	}
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				draw_image(game, (game->wall), x, y);
			else if (game->map[y][x] == '0')
				draw_image(game, (game->background), x, y);
			x++;
		}
		y++;
	}
	draw_player(game);
	draw_coins(game);
	draw_spikes(game);
}

char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;
	int		j;

	copy = (char **)malloc(sizeof(char *) * game->map_height);
	i = 0;
	while (i < game->map_height)
	{
		copy[i] = (char *)malloc(sizeof(char) * game->map_width);
		j = 0;
		while (j < game->map_width)
		{
			copy[i][j] = game->map[i][j];
			j++;
		}
		i++;
	}
	return (copy);
}

void	free_map(char **map, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	can_reach(t_game *game, t_position start, t_position end, char **map_copy)
{
	if (start.x < 0 || start.x >= game->map_width || start.y < 0
		|| start.y >= game->map_height)
		return (0);
	if (map_copy[start.y][start.x] == '1')
		return (0);
	if (start.x == end.x && start.y == end.y)
		return (1);
	map_copy[start.y][start.x] = '1';
	if (can_reach(game, (t_position){start.x + 1, start.y}, end, map_copy))
		return (1);
	if (can_reach(game, (t_position){start.x - 1, start.y}, end, map_copy))
		return (1);
	if (can_reach(game, (t_position){start.x, start.y + 1}, end, map_copy))
		return (1);
	if (can_reach(game, (t_position){start.x, start.y - 1}, end, map_copy))
		return (1);
	return (0);
}

void	error_and_exit(t_game *game, char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	close_game(game);
	exit(EXIT_FAILURE);
}

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

int	can_reach_target(t_game *game, t_position start, t_position target)
{
	char	**map_copy;
	int		is_reachable;

	map_copy = copy_map(game);
	is_reachable = can_reach(game, start, target, map_copy);
	free_map(map_copy, game);
	return (is_reachable);
}

void	check_initial_conditions(t_game *game)
{
	if (game->player.x == -1 || game->player.y == -1)
		error_and_exit(game, "Player not found in the map.");
	if (game->exit.x == -1 || game->exit.y == -1)
		error_and_exit(game, "Exit not found in the map.");
	if (game->num_coins == 0)
		error_and_exit(game, "No coins found in the map.");
	check_walls(game);
}

void	check_player_can_reach_exit(t_game *game, t_position start,
			t_position target)
{
	target.x = game->exit.x;
	target.y = game->exit.y;
	if (!can_reach_target(game, start, target))
		error_and_exit(game, "Player cannot reach the exit.");
}

void	check_player_can_reach_coins(t_game *game, t_list *coins,
			t_position start, t_position target)
{
	t_object	*coin;

	while (coins)
	{
		coin = (t_object *) coins->content;
		if (coin == NULL)
			error_and_exit(game, "coin is not initialized.");
		target.x = coin->x;
		target.y = coin->y;
		if (!can_reach_target(game, start, target))
			error_and_exit(game, "Player cannot reach a coin.");
		coins = coins->next;
	}
}

void	check_map(t_game *game)
{
	t_position	start;
	t_position	target;

	check_initial_conditions(game);
	start.x = game->player.x;
	start.y = game->player.y;
	check_player_can_reach_exit(game, start, target);
	check_player_can_reach_coins(game, game->coins, start, target);
}
