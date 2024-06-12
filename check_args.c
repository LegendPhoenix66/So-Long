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

char	*open_file(char *file)
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
		ft_printf("Error opening file\n");
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
		ft_printf("Error: Expected 1 arguments, received %d\n", argc - 1);
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4))
	{
		ft_printf("Error: File extension should be '.ber'\n");
		exit(1);
	}
}
