/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_reach.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:36:38 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/13 14:09:06 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	can_reach_target(t_game *game, t_position start, t_position target)
{
	char	**map_copy;
	int		is_reachable;

	map_copy = copy_map(game);
	is_reachable = can_reach(game, start, target, map_copy);
	free_map(map_copy, game);
	return (is_reachable);
}
