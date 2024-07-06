/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:03:09 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/27 15:13:19 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define MOVE_UP 0
# define MOVE_DOWN 1
# define MOVE_LEFT 2
# define MOVE_RIGHT 3
# define DESTROY_NOTIFY 17

# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"
# include <fcntl.h>
# include <time.h>

typedef struct s_image
{
	void		*img;
	void		*drawable_img;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_pixel_data_params
{
	int	new_width;
	int	x;
	int	y;
}			t_pixel_data_params;

typedef struct s_object
{
	t_image		*image;
	int			x;
	int			y;
}				t_object;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	int			height;
	int			width;
}				t_window;

typedef struct s_spikes
{
	t_image		*image_on;
	t_image		*image_off;
	int			state;
	int			x;
	int			y;
}				t_spikes;

typedef struct s_game
{
	t_window	window;
	t_image		coin_img;
	t_list		*coins;
	int			num_coins; // number of coins
	t_object	player;
	t_object	exit;
	t_image		background;
	t_image		wall;
	t_image		player_img;
	t_image		exit_img;
	t_list		*spikes;
	t_image		spikes_on;
	t_image		spikes_off;
	char		**map;
	int			map_width;
	int			map_height;
	int			tile_size;
	int			steps;
	char		*file;
	t_list		*portal_images;
}				t_game;

void			check_args(int argc, char **argv);
int				handle_key(int keycode, t_game *param);
t_image			load_image(void *mlx_ptr, char *path, int size);
void			set_drawable_image(void *mlx_ptr, t_image *image, int new_width,
					int new_height);
void			update_drawable_image(t_game *game);
void			update_portal_images(t_game *game);
char			*open_file(t_game *game, char *file);
void			close_game(t_game *game);

void			move_player(t_game *game, int direction);

// map_utils.c
void			calculate_map_size(t_game *game);
void			fill_map(t_game *game);
void			draw_map(t_game *game);
void			check_map(t_game *game);

#endif // SO_LONG_H
