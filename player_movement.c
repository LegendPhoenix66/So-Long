#include "so_long.h"

void	move_player(t_game *game, int direction)
{
	int new_x = game->player.x;
	int new_y = game->player.y;

	if (direction == MOVE_UP)
		new_y--;
	else if (direction == MOVE_DOWN)
		new_y++;
	else if (direction == MOVE_LEFT)
		new_x--;
	else if (direction == MOVE_RIGHT)
		new_x++;

	if (game->map[new_y][new_x] == '1')
		return;

	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->background.drawable_img, game->player.x * game->tile_size,
		game->player.y * game->tile_size);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->player_img.drawable_img, new_x * game->tile_size,
		new_y * game->tile_size);

	game->player.x = new_x;
	game->player.y = new_y;
}