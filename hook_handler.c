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
