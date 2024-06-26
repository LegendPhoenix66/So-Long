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

void	calculate_map_size(t_game *game)
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
			if (game->map_width != 0 && temp_width != game->map_width)
			{
				ft_printf("Error\nMap is not rectangular.\n");
				close_game(game);
				exit(EXIT_FAILURE);
			}
			game->map_width = temp_width;
			temp_width = 0;
		}
		else
		{
			temp_width++;
		}
		i++;
	}
	if (temp_width != game->map_width)
	{
		ft_printf("Error\nMap is not rectangular.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	if (game->map_height == 1 || game->map_width == 0)
	{
		ft_printf("Error\nMap is empty.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
}

void	handle_character(t_game *game, char c, int x, int y)
{
	t_object	*coin;

	if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C')
	{
		ft_printf("Error\nInvalid character in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
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
	if (c == 'P')
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
	else if (c == 'E')
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
	else if (c == 'C')
	{
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

void	draw_map(t_game *game)
{
	t_list		*tmp;
	t_object	*coin;
	int			y;
	int			x;

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
				mlx_put_image_to_window(game->window.mlx, game->window.win,
					game->wall.drawable_img, x * game->tile_size, y
					* game->tile_size);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->window.mlx, game->window.win,
					game->background.drawable_img, x * game->tile_size, y
					* game->tile_size);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->player.image->drawable_img, game->player.x * game->tile_size,
		game->player.y * game->tile_size);
	if (game->num_coins == 0)
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->exit.image->drawable_img, game->exit.x * game->tile_size,
			game->exit.y * game->tile_size);
	tmp = game->coins;
	while (tmp)
	{
		coin = (t_object *)tmp->content;
		if (coin == NULL)
		{
			ft_printf("coin is not initialized.\n");
			return ;
		}
		if (game->window.mlx == NULL)
		{
			ft_printf("game->window.mlx is not initialized.\n");
			return ;
		}
		if (game->window.win == NULL)
		{
			ft_printf("game->window.win is not initialized.\n");
			return ;
		}
		if (coin->image == NULL)
		{
			ft_printf("coin->image is not initialized.\n");
			return ;
		}
		if (coin->image->drawable_img == NULL)
		{
			ft_printf("coin->image->drawable_img is not initialized.\n");
			return ;
		}
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			coin->image->drawable_img, coin->x * game->tile_size, coin->y
			* game->tile_size);
		tmp = tmp->next;
	}
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

int	can_reach(t_game *game, int x1, int y1, int x2, int y2, char **map_copy)
{
	if (x1 < 0 || x1 >= game->map_width || y1 < 0 || y1 >= game->map_height)
	{
		return (0);
	}
	if (map_copy[y1][x1] == '1')
	{
		return (0);
	}
	if (x1 == x2 && y1 == y2)
		return (1);
	map_copy[y1][x1] = '1';
	if (can_reach(game, x1 + 1, y1, x2, y2, map_copy))
		return (1);
	if (can_reach(game, x1 - 1, y1, x2, y2, map_copy))
		return (1);
	if (can_reach(game, x1, y1 + 1, x2, y2, map_copy))
		return (1);
	if (can_reach(game, x1, y1 - 1, x2, y2, map_copy))
		return (1);
	return (0);
}

void	check_map(t_game *game)
{
	char		**map_copy;
	t_list		*tmp;
	t_object	*coin;
	int			x;
	int			y;

	if (game->player.x == -1 || game->player.y == -1)
	{
		ft_printf("Error\nPlayer not found in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	if (game->exit.x == -1 || game->exit.y == -1)
	{
		ft_printf("Error\nExit not found in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	if (game->num_coins == 0)
	{
		ft_printf("Error\nNo coins found in the map.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	// Check top and bottom rows
	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
		{
			ft_printf("Error\nMap is not surrounded by walls.\n");
			close_game(game);
			exit(EXIT_FAILURE);
		}
		x++;
	}
	// Check left and right columns
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
		{
			ft_printf("Error\nMap is not surrounded by walls.\n");
			close_game(game);
			exit(EXIT_FAILURE);
		}
		y++;
	}
	// Check if the player can reach every coin and the exit
	map_copy = copy_map(game);
	if (!can_reach(game, game->player.x, game->player.y, game->exit.x,
			game->exit.y, map_copy))
	{
		ft_printf("Error\nPlayer cannot reach the exit.\n");
		close_game(game);
		exit(EXIT_FAILURE);
	}
	free_map(map_copy, game);
	tmp = game->coins;
	while (tmp)
	{
		coin = (t_object *)tmp->content;
		if (coin == NULL)
		{
			ft_printf("coin is not initialized.\n");
			close_game(game);
			exit(EXIT_FAILURE);
		}
		map_copy = copy_map(game);
		if (!can_reach(game, game->player.x, game->player.y, coin->x, coin->y,
				map_copy))
		{
			ft_printf("Error\nPlayer cannot reach a coin.\n");
			close_game(game);
			exit(EXIT_FAILURE);
		}
		free_map(map_copy, game);
		tmp = tmp->next;
	}
}
