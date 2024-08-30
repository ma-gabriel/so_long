/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:07:39 by geymat            #+#    #+#             */
/*   Updated: 2024/02/14 16:28:09 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_vars(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars);
}

void	delete_textures(void *mlx, t_textures *del)
{
	if (!del)
		return ;
	del->floor && mlx_destroy_image(mlx, del->floor);
	del->wall && mlx_destroy_image(mlx, del->wall);
	del->exit && mlx_destroy_image(mlx, del->exit);
	del->caracter0 && mlx_destroy_image(mlx, del->caracter0);
	del->caracter1 && mlx_destroy_image(mlx, del->caracter1);
	del->collectible && mlx_destroy_image(mlx, del->collectible);
	free(del);
}

void	em_exit(int exit_value, char *message)
{
	write(2, "Error\n", 6);
	if (message)
		write(2, message, ft_strlen(message));
	exit(exit_value);
}

void	end_all(t_thegame *game)
{
	delete_textures(game->vars->mlx, game->textures);
	delete_vars(game->vars);
	argv_free(game->map);
	free(game);
	exit(0);
}
