/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:49:50 by geymat            #+#    #+#             */
/*   Updated: 2024/02/18 12:09:29 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**get_map(char **argv)
{
	size_t	len;
	char	**map;
	int		fd;

	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		em_exit(1, "WHY DID YOU EVEN GIVE A DIRECTORY ???\n");
	}
	len = ft_strlen(argv[1]);
	if (len < 4
		|| argv[1][len - 1] != 'r'
		|| argv[1][len - 2] != 'e'
		|| argv[1][len - 3] != 'b'
		|| argv[1][len - 4] != '.')
		em_exit(1, "the extension has to be \".ber\"\n");
	map = valid_map(open(argv[1], O_RDONLY));
	return (map);
}

int	main(int argc, char **argv)
{
	char		**map;
	t_thegame	*game;

	if (argc == 1)
		em_exit(1, "I need a map. I mean sorry but that's the whole point\n");
	map = get_map(argv);
	game = make_roughly_the_game(map);
	put_textures(map, game->vars, '1', game->textures->wall);
	put_textures(map, game->vars, 'C', game->textures->collectible);
	put_textures(map, game->vars, 'E', game->textures->exit);
	put_textures(map, game->vars, 'P', game->textures->caracter0);
	the_loop_thing(game);
	end_all(game);
}
