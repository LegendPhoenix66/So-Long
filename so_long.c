/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:02:40 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/22 14:03:23 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error opening file\n");
		exit(1);
	}
	char *line = ft_strdup("");
	char *temp = malloc(11 * sizeof(char));
	while (read(fd, temp, 10) > 0)
	{
		line = ft_strjoin(line, temp);
	}
	ft_printf("%s\n", line);
}

void check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Invalid number of arguments\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
	{
		ft_printf("Invalid file extension\n");
		exit(1);
	}
	open_file(argv[1]);
}

int	main(int argc, char **argv)
{
	void	*mlx;

	check_args(argc, argv);
	mlx = mlx_init();
	mlx_new_window(mlx, 1920, 1080, "so_long");
	mlx_loop(mlx);
}
