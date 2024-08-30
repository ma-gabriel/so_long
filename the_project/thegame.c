/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thegame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 07:24:29 by geymat            #+#    #+#             */
/*   Updated: 2024/02/16 09:55:20 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	finish_game(t_thegame *game)
{
	const size_t	collectables = count_caracter_in_map(game->map, 'C');
	const size_t	exits = count_caracter_in_map(game->map, 'E');

	if (collectables || exits)
		return ;
	write(1, "CONGRATS STUDENT FOR CLEANING THE CLUSTER\n", 43);
	end_all(game);
}

int	move_the_player_map(t_thegame *game, int delta_x, int delta_y)
{
	size_t		coo[2];
	static int	exit;

	search_caracter_in_map(game->map, 'P', coo);
	if (game->map[coo[0] + delta_x][coo[1] + delta_y] == '1')
		return (0);
	game->map[coo[0]][coo[1]] = '0' + exit;
	exit || mlx_put_image_to_window(game->vars->mlx, game->vars->win,
		game->textures->floor, coo[1] * SIZE, coo[0] * SIZE);
	exit && mlx_put_image_to_window(game->vars->mlx, game->vars->win,
		game->textures->exit, coo[1] * SIZE, coo[0] * SIZE);
	exit = 0;
	if (game->map[coo[0] + delta_x][coo[1] + delta_y] == 'E')
		exit = 'E' - '0';
	game->map[coo[0] + delta_x][coo[1] + delta_y] = 'P';
	if (delta_y >= 0)
		mlx_put_image_to_window(game->vars->mlx, game->vars->win, game->textures
			->caracter1, (coo[1] + delta_y) * SIZE, (delta_x + coo[0]) * SIZE);
	else
		mlx_put_image_to_window(game->vars->mlx, game->vars->win, game->textures
			->caracter0, (coo[1] + delta_y) * SIZE, (delta_x + coo[0]) * SIZE);
	return (1);
}

t_thegame	*make_roughly_the_game(char **map)
{
	t_thegame	*res;

	res = malloc(sizeof(t_thegame));
	if (!res)
		em_exit(argv_free(map), "another malloc failed\n");
	res->vars = create_window(map);
	if (!res->vars)
	{
		free(res);
		em_exit(argv_free(map), NULL);
	}
	res->textures = get_textures(res->vars->mlx);
	if (!res->textures)
	{
		delete_vars(res->vars);
		free(res);
		em_exit(argv_free(map), "The creation of textures failed\n");
	}
	res->map = map;
	put_textures(map, res->vars, 0, res->textures->floor);
	return (res);
}
