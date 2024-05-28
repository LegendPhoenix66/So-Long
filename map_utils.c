#include "so_long.h"

void calculate_map_size(t_game *game, const char *file)
{
	int i;

	game->map_width = 0;
	game->map_height = 1;
	i = 0;

	// First, count the width and height of the map
	while (file[i] != '\0')
	{
		if (file[i] == '\n')
		{
			game->map_height++;
			game->map_width = 0;
		}
		else
			game->map_width++;
		i++;
	}
}
