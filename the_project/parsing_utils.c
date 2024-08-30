/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:49:50 by geymat            #+#    #+#             */
/*   Updated: 2024/02/16 15:12:57 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	count_caracter_in_map(char **map, char c)
{
	ssize_t	i;
	ssize_t	y;
	ssize_t	res;

	res = 0;
	i = -1;
	while (map[++i])
	{
		y = -1;
		while (map[i][++y])
			if (map[i][y] == c)
				res += 1;
	}
	return (res);
}

void	search_caracter_in_map(char **map, char c, size_t coo[2])
{
	ssize_t	i;
	ssize_t	y;

	i = -1;
	while (map[++i])
	{
		y = -1;
		while (map[i][++y])
		{
			if (map[i][y] == c)
			{
				coo[0] = i;
				coo[1] = y;
				return ;
			}
		}
	}
}

void	rec_propagation(char **map, size_t x, size_t y)
{
	if (map[x][y] == '0')
		map[x][y] = 'V';
	if (map[x][y] == 'C')
		map[x][y] = 'c';
	if (map[x + 1][y] != '1' && map[x + 1][y] != 'V' && map[x + 1][y] != 'c')
		rec_propagation(map, x + 1, y);
	if (map[x - 1][y] != '1' && map[x - 1][y] != 'V' && map[x - 1][y] != 'c')
		rec_propagation(map, x - 1, y);
	if (map[x][y + 1] != '1' && map[x][y + 1] != 'V' && map[x][y + 1] != 'c')
		rec_propagation(map, x, y + 1);
	if (map[x][y - 1] != '1' && map[x][y - 1] != 'V' && map[x][y - 1] != 'c')
		rec_propagation(map, x, y - 1);
}

void	remove_propagation(char **map)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'V')
				map[i][j] = '0';
			if (map[i][j] == 'c')
				map[i][j] = 'C';
		}
	}
}

char	**valid_map(int fd)
{
	char	*line;
	char	buffer[101];
	char	**map;
	ssize_t	bytes;

	bytes = 1;
	if (fd == -1)
		em_exit(1, "the file failed to open.\n");
	line = malloc(1);
	if (line)
		line[0] = 0;
	while (bytes && line)
	{
		bytes = read(fd, buffer, 100);
		buffer[bytes] = 0;
		line = ft_strjoin_free_first(line, buffer);
	}
	if (!line)
		em_exit(1, "a malloc failed.\n");
	map = ft_split(line, '\n');
	free(line);
	if (!map)
		em_exit(1, "a malloc failed.\n");
	check_map(map);
	return (map);
}
