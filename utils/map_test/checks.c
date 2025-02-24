/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:14:00 by vgalloni          #+#    #+#             */
/*   Updated: 2025/02/20 21:59:14 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

bool	ft_dfs_validate_map(char **map, t_check *pos, t_coll *coll)
{
	t_check	temp_pos;

	if (pos->row >= pos->rows || pos->col >= pos->cols
		|| pos->visited[pos->row][pos->col] || map[pos->row][pos->col] == '1' ||
		(map[pos->row][pos->col] != '0' && map[pos->row][pos->col] != 'C' &&
		map[pos->row][pos->col] != 'E' && map[pos->row][pos->col] != 'P'))
		return (false);
	status_pos(map, pos, coll);
	pos->visited[pos->row][pos->col] = true;
	temp_pos = *pos;
	temp_pos.row = pos->row - 1;
	ft_dfs_validate_map(map, &temp_pos, coll);
	temp_pos = *pos;
	temp_pos.row = pos->row + 1;
	ft_dfs_validate_map(map, &temp_pos, coll);
	temp_pos = *pos;
	temp_pos.col = pos->col - 1;
	ft_dfs_validate_map(map, &temp_pos, coll);
	temp_pos = *pos;
	temp_pos.col = pos->col + 1;
	ft_dfs_validate_map(map, &temp_pos, coll);
	return (true);
}

bool	ft_map_closed(char **map, t_check *pos)
{
	unsigned int	col;
	unsigned int	row;

	col = 0;
	row = 0;
	while (col < pos->cols)
	{
		if (map[0][col] != '1' || map[pos->rows - 1][col] != '1')
			return (false);
		col++;
	}
	while (col < pos->cols)
	{
		if (map[row][0] != '1' || map[row][pos->cols - 1] != '1')
			return (false);
		row++;
	}
	return (true);
}

bool	ft_validate_map(char **map, t_check *pos, int re_co, int re_ex)
{
	t_coll	coll;

	coll.collec = 0;
	coll.exit = 0;
	coll.pos = 0;
	if (!ft_map_closed(map, pos))
	{
		ft_printf("validate error");
		return (false);
	}
	ft_dfs_validate_map(map, pos, &coll);
	return (coll.collec == re_co && coll.exit == re_ex && coll.pos == 1);
}

void	ft_cp(t_data *start, t_check *pos)
{
	start->map.col = pos->col;
	start->map.row = pos->row;
	start->map.cols = pos->cols;
	start->map.rows = pos->rows;
	start->map.off_x = 0.5;
	start->map.off_y = 0.5;
}

void	ft_clean_map(char ***map, int i)
{
	int	index;
	int	j;

	index = 0;
	while (index < i)
	{
		j = 0;
		while ((*map)[index][j])
		{
			if ((*map)[index][j] == '\n')
				(*map)[index][j] = '\0';
			j++;
		}
		index++;
	}
}
