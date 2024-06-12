/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:06:43 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/12 16:38:28 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/keysym.h>

int	handle_key(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		mlx_loop_end(game->window.mlx);
	}
	else if (keycode == XK_Up || keycode == XK_W || keycode == 119)
	{
		move_player(game, MOVE_UP);
	}
	else if (keycode == XK_Down || keycode == XK_S || keycode == 115)
	{
		move_player(game, MOVE_DOWN);
	}
	else if (keycode == XK_Left || keycode == XK_A || keycode == 97)
	{
		move_player(game, MOVE_LEFT);
	}
	else if (keycode == XK_Right || keycode == XK_D || keycode == 100)
	{
		move_player(game, MOVE_RIGHT);
	}
	return (0);
}
