/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:03:09 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/28 11:56:24 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"
# include <fcntl.h>

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

typedef struct s_object
{
	t_image		image;
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

typedef struct s_game
{
	t_window	window;
	t_object	coin; // one coin
	t_list		*coins;
	int			num_coins; // number of coins
	t_object	player;
	t_object	exit;
	t_image		background;
	t_image		wall;
	char		**map;
	int			map_width;
	int			map_height;
	int			tile_size;
}				t_game;

void			check_args(int argc, char **argv);
int				handle_key(int keycode, t_window *param);
int				handle_mouse(int button, int x, int y, t_window *window);
t_image			copy_image(void *mlx_ptr, t_image *image, int x, int y,
					int width, int height);
t_image			load_image(void *mlx_ptr, char *path, int width, int height);
char			*open_file(char *file);
void			close_game(t_game *game);

// map_utils.c
void			calculate_map_size(t_game *game, const char *file);

#endif // SO_LONG_H
