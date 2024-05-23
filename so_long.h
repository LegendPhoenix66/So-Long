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

#endif // SO_LONG_H
