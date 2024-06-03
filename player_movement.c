#include "so_long.h"

void check_tile(t_game *game, int x, int y) {
    // check for coin
    t_list *tmp = game->coins;
    while (tmp) {
        t_object *coin = (t_object *) tmp->content;
        if (coin->x == x && coin->y == y) {
            // remove coin from list
            if (tmp == game->coins) {
                game->coins = tmp->next;
                ft_lstdelone(tmp, free);
            } else {
                t_list *prev = game->coins;
                while (prev->next != tmp)
                    prev = prev->next;
                prev->next = tmp->next;
                ft_lstdelone(tmp, free);
            }
            game->num_coins--;
            // if no coins left, draw exit
            if (game->num_coins == 0) {
                mlx_put_image_to_window(game->window.mlx, game->window.win,
                                        game->exit_img.drawable_img, game->exit.x * game->tile_size,
                                        game->exit.y * game->tile_size);
            }
        }
        tmp = tmp->next;
    }
    // check for exit
    if (game->player.x == game->exit.x && game->player.y == game->exit.y && game->num_coins == 0) {
        ft_printf("You win!\n");
        mlx_loop_end(game->window.mlx);
    }
}

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
    game->steps++;
    ft_printf("Steps: %d\n", game->steps);
    check_tile(game, new_x, new_y);
}