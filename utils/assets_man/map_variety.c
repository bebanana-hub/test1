/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_variety.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:49:13 by vgalloni          #+#    #+#             */
/*   Updated: 2025/02/20 18:12:31 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	ft_variety(char **map, int ***temp, t_data data)
{
	t_co	co;

	co.y = 0;
	while (co.y < data.map.rows)
	{
		co.x = 0;
		while (co.x < data.map.cols)
		{
			if (map[co.y][co.x] == '1')
				(*temp)[co.y][co.x] = IN_WL;
			if (map[co.y][co.x] == '0')
				(*temp)[co.y][co.x] = IN_GR1;
			if (map[co.y][co.x] == 'P')
				(*temp)[co.y][co.x] = IN_GR3;
			if (map[co.y][co.x] == 'E')
				(*temp)[co.y][co.x] = IN_CL_EX;
			if (map[co.y][co.x] == 'C')
				(*temp)[co.y][co.x] = IN_COLL_FULL;
			co.x++;
		}
		co.y++;
	}
	return ;
}

int	**ft_mapgen(char **map, t_data data)
{
	int				**temp;
	unsigned int	i;

	i = 0;
	temp = malloc((data.map.rows + 1) * sizeof(int *));
	if (!temp)
		return (ft_free_arr((void **)map, data.map.rows), NULL);
	while (i < data.map.rows)
	{
		temp[i] = malloc(data.map.cols * sizeof(int));
		if (!temp[i])
		{
			ft_free_arr((void **)map, data.map.rows);
			return (ft_free_arr((void **)temp, i), NULL);
		}
		i++;
	}
	ft_variety(map, &temp, data);
	ft_free_arr((void **)map, data.map.rows);
	return (temp);
}
