/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:03:09 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/23 12:08:50 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"
# include <fcntl.h>

typedef struct s_window
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}			t_window;

void		check_args(int argc, char **argv);
int			handle_key(int keycode, t_window *param);
int			handle_mouse(int button, int x, int y, t_window *window);
t_image copy_image(void *mlx_ptr, t_image *image, int x, int y, int width, int height);
t_image load_image(void *mlx_ptr, char *path, int width, int height);
char	*open_file(char *file);
void close_game(t_game *game);

#endif // SO_LONG_H
