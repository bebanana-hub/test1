/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_callback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:41:45 by vincent           #+#    #+#             */
/*   Updated: 2025/02/20 19:16:39 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	show_exit(t_data *data)
{
	data->img[IN_CL_EX]->instances[0].enabled = 0;
	data->img[IN_OP_EX]->instances[0].enabled = 1;
	data->exit_op = 1;
}

int	ft_collision(t_data *dt, int ***map, t_co co)
{
	int	inst;

	inst = map[1][co.y][co.x];
	if (map[0][co.y][co.x] == IN_WL)
		return (1);
	if (map[0][co.y][co.x] == IN_COLL_FULL)
	{
		dt->inventory++;
		dt->img[IN_COLL_FULL]->instances[inst].enabled = 0;
		dt->img[IN_COLL_EMPTY]->instances[inst].enabled = 1;
	}
	if (dt->inventory == dt->collec && !dt->exit_op)
		show_exit(dt);
	if (map[0][co.y][co.x] == IN_CL_EX && dt->exit_op)
	{
		ft_printf("you've won !!\n");
		ft_on_exit(dt);
	}
	return (0);
}

void	ft_update_bis(t_data *dt, int ***map, t_co_s o, t_co co)
{
	t_co	in;

	o.x = (dt->pos.x - co.x) * TILE;
	o.y = (dt->pos.y - co.y) * TILE;
	in.y = 0;
	while (in.y < dt->map.rows)
	{
		in.x = 0;
		while (in.x < dt->map.cols)
		{
			dt->img[map[0][in.y][in.x]]->instances[map[1][in.y][in.x]].x += o.x;
			dt->img[map[0][in.y][in.x]]->instances[map[1][in.y][in.x]].y += o.y;
			if (map[0][in.y][in.x] == 4 || map[0][in.y][in.x] == 6)
				ft_mv_mt(dt, map, in, o);
			in.x++;
		}
		in.y++;
	}
	dt->move++;
	ft_printf("moves:%i\n", dt->move);
	dt->pos = co;
}

void	update(t_data *data, int dir, bool *can_move)
{
	t_co	co;

	co.y = data->pos.y;
	co.x = data->pos.x;
	if (!(*can_move))
		return ;
	if (dir == UP)
		co.y--;
	if (dir == DOWN)
		co.y++;
	if (dir == LEFT)
		co.x--;
	if (dir == RIGHT)
		co.x++;
	if (!ft_collision(data, data->i_map, co))
		ft_update_bis(data, data->i_map, data->off, co);
	*can_move = false;
}

void	ft_key_callback(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		return (ft_on_exit(data));
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		update(data, UP, &(data->can_move.up));
	else
		data->can_move.up = true;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		update(data, DOWN, &(data->can_move.down));
	else
		data->can_move.down = true;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		update(data, LEFT, &(data->can_move.left));
	else
		data->can_move.left = true;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		update(data, RIGHT, &(data->can_move.right));
	else
		data->can_move.right = true;
}
