/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:06:43 by vgalloni          #+#    #+#             */
/*   Updated: 2025/02/20 19:54:26 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	char	**map;
	t_data	data;

	if (ac != 2)
		return (ft_error("invalid arguments"), 0);
	if (!check_format(av[1]))
		return (ft_error("map format is wrong"), 1);
	if (!ft_map_check(av[ac - 1], &map, &data))
		return (ft_error("invalid map"), 1);
	data.i_map[0] = ft_mapgen(map, data);
	if (!data.i_map[0])
		return (perror("int map malloc"), 1);
	if (!ft_temp(&data.i_map[1], data))
		return (ft_free_arr((void **)data.i_map[0], data.map.rows), 1);
	if (!ft_init_textures(data.tx))
		return (ft_free_da(data.i_map, data.map.rows), 1);
	init_move(&data);
	ft_game(data.i_map, &data);
	ft_free_da(data.i_map, data.map.rows);
	return (0);
}

int	ft_temp(int ***temp, t_data data)
{
	unsigned int	i;

	*temp = malloc((data.map.rows + 1) * sizeof(int *));
	if (!(*temp))
		return (0);
	i = 0;
	while (i < data.map.rows)
	{
		(*temp)[i] = malloc((data.map.cols + 1) * sizeof(int));
		if (!(*temp)[i])
			return (ft_free_arr((void **)(*temp), i), 0);
		i++;
	}
	return (1);
}

int	ft_init_textures(mlx_texture_t	**texture)
{
	int	i;

	i = 0;
	while (i < MAX_TEXTURE)
	{
		texture[i] = mlx_load_png(g_a_path[i]);
		if (!texture[i])
			return (ft_free_tx(texture, i), 0);
		i++;
	}
	return (1);
}

int	ft_game(int ***map, t_data *data)
{
	data->exit_op = 0;
	data->move = 0;
	data->mlx = mlx_init(WIN_W, WIN_H, "test", false);
	if (!data->mlx)
		return (ft_error(mlx_strerror(mlx_errno)), ft_error("test"), 0);
	ft_render(data, map);
	ft_move(data, map);
	mlx_key_hook(data->mlx, ft_key_callback, data);
	mlx_loop(data->mlx);
	ft_on_exit(data);
	return (1);
}

void	init_move(t_data *data)
{
	data->can_move.up = true;
	data->can_move.down = true;
	data->can_move.left = true;
	data->can_move.right = true;
}
