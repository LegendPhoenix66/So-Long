#include "so_long.h"

void destroy_image(t_game *game, t_image *image)
{
	mlx_destroy_image(game->window.mlx, image->img);
	mlx_destroy_image(game->window.mlx, image->drawable_img);
}

void close_game(t_game *game)
{
	destroy_image(game, &game->background);
	destroy_image(game, &game->wall);
	destroy_image(game, &game->player.image);
	destroy_image(game, &game->exit.image);
	destroy_image(game, &game->coin.image);

	mlx_destroy_window(game->window.mlx, game->window.win);
	mlx_destroy_display(game->window.mlx);
	free(game->window.mlx);
}