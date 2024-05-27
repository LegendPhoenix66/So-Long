#include "so_long.h"

void    *resize_image(void *mlx_ptr, t_image *image, int new_width, int new_height)
{
	int     bpp;
	int     size_line;
	int     endian;
	char    *old_data;
	char    *new_data;
	void    *new_img;
	int     x;
	int     y;

	old_data = mlx_get_data_addr(image->img, &image->bpp, &image->size_line, &image->endian);
	new_img = mlx_new_image(mlx_ptr, new_width, new_height);
	new_data = mlx_get_data_addr(new_img, &bpp, &size_line, &endian);

	y = 0;
	while (y < new_height)
	{
		x = 0;
		while (x < new_width)
		{
			new_data[(y * new_width + x) * (bpp / 8)] = old_data[(y * image->height / new_height * image->width + x * image->width / new_width) * (bpp / 8)];
			new_data[(y * new_width + x) * (bpp / 8) + 1] = old_data[(y * image->height / new_height * image->width + x * image->width / new_width) * (bpp / 8) + 1];
			new_data[(y * new_width + x) * (bpp / 8) + 2] = old_data[(y * image->height / new_height * image->width + x * image->width / new_width) * (bpp / 8) + 2];
			new_data[(y * new_width + x) * (bpp / 8) + 3] = old_data[(y * image->height / new_height * image->width + x * image->width / new_width) * (bpp / 8) + 3];
			x++;
		}
		y++;
	}
	return (new_img);
}

t_image load_image(void *mlx_ptr, char *path, int width, int height)
{
	t_image image;

	image.img = mlx_xpm_file_to_image(mlx_ptr, path, &image.width, &image.height);
	if (!image.img)
	{
		// Handle error
		exit(1);
	}
	image.drawable_img = resize_image(mlx_ptr, &image, width, height);
	return (image);
}

t_image copy_image(void *mlx_ptr, t_image *image, int x, int y, int width, int height)
{
	t_image new_image;
	char *old_data;
	char *new_data;
	int bpp;
	int size_line;
	int endian;

	new_image.img = mlx_new_image(mlx_ptr, width, height);
	new_image.width = width;
	new_image.height = height;
	int x_copy = x;
	old_data = mlx_get_data_addr(image->img, &bpp, &size_line, &endian);
	new_data = mlx_get_data_addr(new_image.img, &bpp, &size_line, &endian);

	while (y < height)
	{
		x = x_copy;
		while (x < width)
		{
			new_data[(y * width + x) * (bpp / 8)] = old_data[(y * image->height + x) * (bpp / 8)];
			x++;
		}
		y++;
	}
	return (new_image);
}
