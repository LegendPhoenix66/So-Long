/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:07:18 by lhopp             #+#    #+#             */
/*   Updated: 2024/05/23 12:20:46 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*open_file(t_game *game, char *file)
{
	int		fd;
	char	*line;
	char	*temp;
	char	*new_line;
	size_t	chunk_size;

	chunk_size = 1024;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nCould not open file\n");
		close_game(game);
		exit(1);
	}
	line = ft_strdup("");
	temp = ft_calloc(chunk_size + 1, sizeof(char));
	while (read(fd, temp, chunk_size) > 0)
	{
		new_line = ft_strjoin(line, temp);
		free(line);
		line = new_line;
	}
	free(temp);
	close(fd);
	return (line);
}

void	check_args(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		ft_printf("Error\nExpected 1 arguments, received %d\n", argc - 1);
		exit(1);
	}
	// argv[1] can contain the path to the file, I only want the file name
	char *file_name = ft_strrchr(argv[1], '/');
	// remove the starting '/' from the file name
	if (file_name)
		file_name++;
	else
		file_name = argv[1];
	len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp(file_name + len - 4, ".ber", 4))
	{
		ft_printf("Error\nFile extension should be '.ber'\n");
		exit(1);
	} else if (len == 4)
	{
		ft_printf("Error\nFile name should not be empty\n");
		exit(1);
	}
}
