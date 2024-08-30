/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:20:12 by geymat            #+#    #+#             */
/*   Updated: 2024/02/16 15:12:35 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map(char **map)
{
	size_t	coo[2];

	if (!*map)
	{
		free(map);
		em_exit(1, "the map file is empty");
	}
	check_form(map);
	check_caracters(map);
	search_caracter_in_map(map, 'P', coo);
	rec_propagation(map, coo[0], coo[1]);
	check_access(map);
	remove_propagation(map);
}

void	check_access(char **map)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'C' || (map[i][j] == 'E' && !(map[i + 1][j]
				== 'V' || map[i - 1][j] == 'V' || map[i][j + 1]
				== 'V' || map[i][j - 1] == 'V' || map[i + 1][j]
				== 'c' || map[i - 1][j] == 'c' || map[i][j + 1]
				== 'c' || map[i][j - 1] == 'c')))
				em_exit(argv_free(map), "you won't be able to "
					"access everything and then to leave\n");
	}
}

void	check_caracters(char **map)
{
	if (count_caracter_in_map(map, 'P') != 1)
		em_exit(argv_free(map), "The map must have exactly one start\n");
	if (!count_caracter_in_map(map, 'C'))
		em_exit(argv_free(map), "The map doesn't have collectibles\n");
	if (count_caracter_in_map(map, 'E') != 1)
		em_exit(argv_free(map), "The map must have exactly one exit\n");
	if (count_caracter_in_map(map, 'E') + count_caracter_in_map(map, '0')
		+ count_caracter_in_map(map, '1') + count_caracter_in_map(map, 'P')
		+ count_caracter_in_map(map, 'C') != ft_strlen(*map)
		* ft_bigstrlen(map))
		em_exit(argv_free(map), "the map must have only 0 1 C E P\n");
}

void	check_form(char **map)
{
	const size_t	x = ft_strlen(*map);
	const size_t	y = ft_bigstrlen(map);
	ssize_t			i;

	i = -1;
	while (map[++i])
		if (ft_strlen(map[i]) != x)
			em_exit(argv_free(map), "The map isn't a rectangle\n");
	i = -1;
	while (map[0][++i])
		if (map[0][i] != '1')
			em_exit(argv_free(map), "The map isn't closed at the top\n");
	i = -1;
	while (map[y - 1][++i])
		if (map[y - 1][i] != '1')
			em_exit(argv_free(map), "The map isn't closed at the bottom\n");
	i = -1;
	while (map[++i])
		if (map[i][0] != '1' || map[i][x - 1] != '1')
			em_exit(argv_free(map), "The map isn't closed at the sides\n");
}
