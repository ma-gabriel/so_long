/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:54:04 by geymat            #+#    #+#             */
/*   Updated: 2024/02/18 11:46:45 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>

# ifndef SIZE
#  define SIZE 64
# endif

typedef struct s_vars
{
	void	*mlx;
	size_t	height;
	size_t	width;
	void	*win;
}				t_vars;

typedef struct s_textures
{
	void	*caracter0;
	void	*caracter1;
	void	*collectible;
	void	*floor;
	void	*wall;
	void	*exit;
}				t_textures;

typedef struct s_thegame
{
	t_vars		*vars;
	t_textures	*textures;
	char		**map;
}				t_thegame;

char		**ft_split(char const *s, char c);
size_t		ft_strlen(char *str);
size_t		ft_bigstrlen(char **str);
void		em_exit(int exit_value, char *message);
int			argv_free(char **argv);
t_vars		*create_window(char **map);
t_thegame	*make_roughly_the_game(char **map);
void		delete_vars(t_vars *vars);
t_textures	*get_textures(void *mlx);
void		delete_textures(void *mlx, t_textures *del);
void		put_textures(char **map, t_vars *vars, char replace, void *texture);
void		end_all(t_thegame *game);
void		the_loop_thing(t_thegame *game);
void		search_caracter_in_map(char **map, char c, size_t coo[2]);
int			move_the_player_map(t_thegame *game, int delta_x, int delta_y);
void		finish_game(t_thegame *game);
size_t		count_caracter_in_map(char **map, char c);
void		check_map(char **map);
void		check_access(char **map);
void		check_caracters(char **map);
void		check_form(char **map);
void		rec_propagation(char **map, size_t x, size_t y);
void		remove_propagation(char **map);
char		*ft_strjoin_free_first(char *s1, char *s2);
char		**valid_map(int fd);

#endif
