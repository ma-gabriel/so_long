/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:58:51 by geymat            #+#    #+#             */
/*   Updated: 2024/02/16 12:02:54 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "so_long.h"

void	put_textures(char **map, t_vars *vars, char replace, void *texture)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == replace || !replace)
				mlx_put_image_to_window(vars->mlx, vars->win, texture,
					j * SIZE, i * SIZE);
	}
}

t_vars	*create_window(char **map)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return ((t_vars *)(0 * write(2,
				"Error\na malloc failed, the 'create_window' one\n", 48)));
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		free(vars);
		write(2, "Error\nmlx didn't initialized LOL\n", 34);
		return (NULL);
	}
	vars->width = ft_strlen(*map) * SIZE;
	vars->height = ft_bigstrlen(map) * SIZE;
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "so_long");
	if (!vars->win)
	{
		free(vars->mlx);
		free(vars);
		write(2, "Error\nmlx window didn't initialized LOL\n", 41);
		return (NULL);
	}
	return (vars);
}

t_textures	*get_textures(void *mlx)
{
	t_textures	*res;
	int			bin;
	int			bin2;

	res = malloc(sizeof(t_textures));
	if (!res)
		return (NULL);
	res->floor = mlx_xpm_file_to_image(mlx, "./textures/floor.xpm",
			&bin, &bin2);
	res->wall = mlx_xpm_file_to_image(mlx, "./textures/wall.xpm", &bin, &bin2);
	res->exit = mlx_xpm_file_to_image(mlx, "./textures/exit.xpm", &bin, &bin2);
	res->caracter0 = mlx_xpm_file_to_image(mlx, "./textures/caracter0.xpm",
			&bin, &bin2);
	res->caracter1 = mlx_xpm_file_to_image(mlx, "./textures/caracter1.xpm",
			&bin, &bin2);
	res->collectible = mlx_xpm_file_to_image(mlx,
			"./textures/collectible.xpm", &bin, &bin);
	if (!(res->floor && res->wall && res->exit && res->caracter0
			&& res->caracter1 && res->collectible))
	{
		delete_textures(mlx, res);
		return (NULL);
	}
	return (res);
}
