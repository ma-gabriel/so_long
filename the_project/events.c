/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:55:16 by geymat            #+#    #+#             */
/*   Updated: 2024/02/16 11:20:00 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_putsize_t(size_t n)
{
	char	temp;

	if (n == 18446744073709551615UL)
	{
		write(1, "18446744073709551615", 20);
		return ;
	}
	if (!n)
	{
		write(1, "0", 1);
		return ;
	}
	if (n / 10)
		ft_putsize_t(n / 10);
	temp = n % 10 + '0';
	write (1, &temp, 1);
}

static int	function_hub(int key_value, void *game)
{
	static size_t	nb_moves;
	int				temp;

	temp = 0;
	if (key_value != 65307 && key_value != 97 && key_value != 115
		&& key_value != 119 && key_value != 100)
		return (0);
	if (!game)
		return (write(2, "Error\nHow did it even happen ??\n", 33));
	if (key_value == 65307 && write(1, "It was a pleasure\n", 18))
		end_all(game);
	temp = move_the_player_map(game, (key_value == 115 || key_value == 119)
			* ((key_value == 115) * 2 - 1), (key_value == 100
				|| key_value == 97) * ((key_value == 100) * 2 - 1));
	if (!temp)
		return (0);
	nb_moves += 1;
	write (1, "Moves : ", 8);
	ft_putsize_t(nb_moves);
	write(1, "\n", 1);
	finish_game(game);
	return (0);
}

static int	destroy_by_button(void *game, int key_code_305)
{
	if (key_code_305 != 305)
		return (1);
	write(1, "It was a pleasure\n", 18);
	end_all(game);
	return (0);
}

void	the_loop_thing(t_thegame *game)
{
	mlx_key_hook(game->vars->win, function_hub, game);
	mlx_hook(game->vars->win, 17, 0, destroy_by_button, game);
	mlx_loop(game->vars->mlx);
}
