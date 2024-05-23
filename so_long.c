/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:02:40 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/23 12:08:39 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define DESTROY_NOTIFY 17

int	main(int argc, char **argv)
{
	t_window	window;

	check_args(argc, argv);
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, 1920, 1080, "so_long");
	mlx_key_hook(window.win, handle_key, &window);
	mlx_mouse_hook(window.win, handle_mouse, &window);
	mlx_hook(window.win, DESTROY_NOTIFY, 0, &mlx_loop_end, window.mlx);
	mlx_loop(window.mlx);
	mlx_destroy_window(window.mlx, window.win);
	mlx_destroy_display(window.mlx);
	free(window.mlx);
	return (0);
}
