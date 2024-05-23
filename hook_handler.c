/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:06:43 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/23 12:08:46 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/keysym.h>

int	handle_key(int keycode, t_window *window)
{
	if (keycode == XK_Escape)
	{
		mlx_loop_end(window->mlx);
	}
	return (0);
}

int	handle_mouse(int button, int x, int y, t_window *window)
{
	if (button == 1)
	{
		mlx_pixel_put(window->mlx, window->win, x, y, 0x00FF0000);
	}
	return (0);
}
