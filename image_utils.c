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

int	calculate_old_index(t_position pos, int new_width, int new_height,
			t_image *image)
{
	return ((pos.y * image->height / new_height * image->width
			+ pos.x * image->width / new_width)
		* (image->bpp / 8));
}

int	calculate_new_index(t_position pos, int new_width, t_image *image)
{
	return ((pos.y * new_width + pos.x) * (image->bpp / 8));
}

void	process_image(char *original_pixels, char *resized_pixels,
		t_position new_size, t_image *image)
{
	int			old_index;
	int			new_index;
	t_position	pos;
	int			i;

	pos.y = 0;
	while (pos.y < new_size.y)
	{
		pos.x = 0;
		while (pos.x < new_size.x)
		{
			old_index = calculate_old_index(pos, new_size.x, new_size.y, image);
			new_index = calculate_new_index(pos, new_size.x, image);
			i = 0;
			while (i < 4)
			{
				resized_pixels[new_index + i] = original_pixels[old_index + i];
				i++;
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	set_drawable_image(void *mlx_ptr, t_image *image, int new_width,
		int new_height)
{
	char		*original_pixels;
	char		*resized_pixels;
	t_position	new_size;

	original_pixels = mlx_get_data_addr(image->img, &image->bpp,
			&image->size_line, &image->endian);
	image->drawable_img = mlx_new_image(mlx_ptr, new_width, new_height);
	resized_pixels = mlx_get_data_addr(image->drawable_img, &image->bpp,
			&image->size_line, &image->endian);
	new_size.x = new_width;
	new_size.y = new_height;
	process_image(original_pixels, resized_pixels, new_size, image);
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
