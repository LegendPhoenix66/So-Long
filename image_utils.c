/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:55:50 by lhopp             #+#    #+#             */
/*   Updated: 2024/06/27 15:10:39 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_drawable_image(void *mlx_ptr, t_image *image, int new_width,
		int new_height)
{
	char	*old_data;
	char	*new_data;
	int		x;
	int		y;

	old_data = mlx_get_data_addr(image->img, &image->bpp, &image->size_line,
			&image->endian);
	image->drawable_img = mlx_new_image(mlx_ptr, new_width, new_height);
	new_data = mlx_get_data_addr(image->drawable_img, &image->bpp,
			&image->size_line, &image->endian);
	y = 0;
	while (y < new_height)
	{
		x = 0;
		while (x < new_width)
		{
			new_data[(y * new_width + x) * (image->bpp / 8)] = old_data[(y
					* image->height / new_height * image->width + x
					* image->width / new_width) * (image->bpp / 8)];
			new_data[(y * new_width + x) * (image->bpp / 8) + 1] = old_data[(y
					* image->height / new_height * image->width + x
					* image->width / new_width) * (image->bpp / 8) + 1];
			new_data[(y * new_width + x) * (image->bpp / 8) + 2] = old_data[(y
					* image->height / new_height * image->width + x
					* image->width / new_width) * (image->bpp / 8) + 2];
			new_data[(y * new_width + x) * (image->bpp / 8) + 3] = old_data[(y
					* image->height / new_height * image->width + x
					* image->width / new_width) * (image->bpp / 8) + 3];
			x++;
		}
		y++;
	}
}

t_image	load_image(void *mlx_ptr, char *path, int size)
{
	t_image	image;

	image.img = mlx_xpm_file_to_image(mlx_ptr, path, &image.width,
			&image.height);
	if (!image.img)
	{
		exit(1);
	}
	set_drawable_image(mlx_ptr, &image, size, size);
	return (image);
}

void	update_drawable_image(t_game *game)
{
	mlx_destroy_image(game->window.mlx, game->coin_img.drawable_img);
	set_drawable_image(game->window.mlx, &game->coin_img, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->background.drawable_img);
	set_drawable_image(game->window.mlx, &game->background, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->wall.drawable_img);
	set_drawable_image(game->window.mlx, &game->wall, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->player_img.drawable_img);
	set_drawable_image(game->window.mlx, &game->player_img, game->tile_size,
		game->tile_size);
	mlx_destroy_image(game->window.mlx, game->exit_img.drawable_img);
	set_drawable_image(game->window.mlx, &game->exit_img, game->tile_size,
		game->tile_size);
}

void	update_portal_images(t_game *game)
{
	t_list	*tmp;
	int		i;
	t_list	*first;

	tmp = game->portal_images;
	i = 0;
	if (tmp != NULL)
	{
		first = tmp;
		while (tmp->next != first)
		{
			mlx_destroy_image(game->window.mlx,
				((t_image *)tmp->content)->drawable_img);
			set_drawable_image(game->window.mlx, (t_image *)tmp->content,
				game->tile_size, game->tile_size);
			tmp = tmp->next;
			i++;
		}
		mlx_destroy_image(game->window.mlx,
			((t_image *)tmp->content)->drawable_img);
		set_drawable_image(game->window.mlx, (t_image *)tmp->content,
			game->tile_size, game->tile_size);
	}
}
