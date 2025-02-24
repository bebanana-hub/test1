/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:26:27 by vgalloni          #+#    #+#             */
/*   Updated: 2025/02/20 21:54:07 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <fcntl.h>
# include "./lib/lib42/lib42.h"
# include "./lib/mlx42/include/MLX42/MLX42.h"
# include "assets.h"

# define TILE 160
//* 32 "pixels" * 5 real pixels per "pixels"

# define WIN_H 750
# define WIN_W 1000

# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

// ! utilite provee
typedef struct s_check
{
	unsigned int	col;
	unsigned int	row;
	unsigned int	cols;
	unsigned int	rows;
	bool			**visited;
}	t_check;

// ! utilite provee
typedef struct s_co
{
	unsigned int	x;
	unsigned int	y;
}	t_co;

typedef struct s_co_s
{
	int	x;
	int	y;
}	t_co_s;

// ! utilite provee
typedef struct s_coll
{
	int	exit;
	int	collec;
	int	pos;
}	t_coll;

// ! utilite provee
typedef struct s_map
{
	unsigned int	col;
	unsigned int	row;
	unsigned int	cols;
	unsigned int	rows;
	float			off_x;
	float			off_y;
}	t_map;

typedef struct s_can_move
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}	t_can_move;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_texture_t	*tx[MAX_TEXTURE];
	mlx_image_t		*img[MAX_TEXTURE];
	mlx_image_t		*b_gr;
	int				collec;
	int				inventory;
	t_map			map;
	bool			exit_op;
	int				**i_map[2];
	t_co			pos;
	t_co_s			off;
	t_can_move		can_move;
	int				move;
}	t_data;

//* in main.c
int		ft_game(int ***map, t_data *data);
int		ft_init_textures(mlx_texture_t	**texture);
int		ft_temp(int ***temp, t_data data);
void	init_move(t_data *data);

//* in map_test/checks.c
bool	ft_dfs_validate_map(char **map, t_check *pos, t_coll *coll);
bool	ft_map_closed(char **map, t_check *pos);
bool	ft_validate_map(char **map, t_check *pos, int re_co, int re_ex);
void	ft_cp(t_data *start, t_check *pos);
void	ft_clean_map(char ***map, int i);

//* in map_test/get_map.c
int		ft_map_check(char *map_file, char ***map, t_data *start);
char	**ft_get_map(t_check *pos, int fd, char **map);
bool	ft_is_rectangle(t_check *pos, char **map, int *collec, int *exit);
void	ft_init_visited(t_check *pos);
void	ft_get_start(t_check *pos, int i, char *temp);

//* in assets_man/map_variety.c
void	ft_variety(char **map, int ***temp, t_data data);
int		**ft_mapgen(char **map, t_data data);

//* in err_man/err_man.c
void	ft_free_tx(mlx_texture_t **texture, int max);
void	ft_free_da(int ***temp, int max);
void	ft_err(void);
void	ft_delimg(t_data *data, mlx_image_t **img, int max);
void	ft_on_exit(t_data *data);

//* in err_man/err_man2.c
void	status_pos(char **map, t_check *pos, t_coll *coll);
int		check_format(char *str);

//* in assets_man/render.c
int		ft_render(t_data *data, int ***map);
int		ft_resized(t_data *data, mlx_image_t **img);
void	ft_player(t_data *data, const uint32_t width, const uint32_t height);
int		ft_background(t_data *data, mlx_image_t *img);
void	ft_render_false(t_data *data, t_co co, int ***map);

//* in assets_man/mouvment.c
int		ft_move(t_data *data, int ***map);
void	ft_mv_mt(t_data *data, int ***map, t_co co, t_co_s ofs);

//* in assets_man/ft_key_callback.c
void	ft_key_callback(mlx_key_data_t keydata, void *param);
void	update(t_data *data, int dir, bool *can_move);
void	ft_update_bis(t_data *dt, int ***map, t_co_s ofs, t_co co);
int		ft_collision(t_data *dt, int ***map, t_co co);
void	show_exit(t_data *data);

#endif
