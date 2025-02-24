/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:16:05 by vincent           #+#    #+#             */
/*   Updated: 2025/02/20 18:17:51 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	ft_move(t_data *dt, int ***map)
{
	t_co	co;
	t_co_s	o;

	o.x = (WIN_W / 2 - TILE / 2) - (dt->map.col * TILE);
	o.y = (WIN_H / 2 - TILE / 2) - (dt->map.row * TILE);
	co.y = 0;
	while (co.y < dt->map.rows)
	{
		co.x = 0;
		while (co.x < dt->map.cols)
		{
			dt->img[map[0][co.y][co.x]]->instances[map[1][co.y][co.x]].x += o.x;
			dt->img[map[0][co.y][co.x]]->instances[map[1][co.y][co.x]].y += o.y;
			if (map[0][co.y][co.x] == 4 || map[0][co.y][co.x] == 6)
				ft_mv_mt(dt, map, co, o);
			co.x++;
		}
		co.y++;
	}
	return (1);
}

void	ft_mv_mt(t_data *data, int ***map, t_co co, t_co_s ofs)
{
	data->img[map[0][co.y][co.x] + 1]->instances[map[1][co.y][co.x]].x += ofs.x;
	data->img[map[0][co.y][co.x] + 1]->instances[map[1][co.y][co.x]].y += ofs.y;
}
